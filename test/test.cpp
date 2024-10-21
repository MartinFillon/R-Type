#include "test.hpp"
#include <asio.hpp>
#include <iostream>
#include <memory>
#include <string>

using asio::ip::tcp;

TCPCommunication::TCPCommunication(tcp::socket socket, int client_number)
    : _socket(std::move(socket)), _client_number(client_number)
{
}

void TCPCommunication::start()
{
    readClient();
}

void TCPCommunication::readClient()
{
    auto self(shared_from_this());

    asio::async_read_until(
        _socket,
        asio::dynamic_buffer(_data),
        '\n',
        [this, self](std::error_code ec, std::size_t length) {

            if (!ec) {
                std::cout << "from client #" << _client_number << ": " << _data.substr(0, length) << std::endl;

                std::string message = "from client #" + std::to_string(_client_number) + ": " + _data.substr(0, length);
                writeToClient(message);
            } else {
                std::cerr << ec.message() << std::endl;

            }
        }
    );
}

void TCPCommunication::writeToClient(const std::string &message)
{
    auto self(shared_from_this());

    asio::async_write(_socket, asio::buffer(message + "\n"), [this, self](std::error_code ec, std::size_t /*length*/) {
        if (!ec) {
            _data.clear();
            readClient();
        } else {
            std::cerr << "Erreur d'écriture: " << ec.message() << std::endl;
            _socket.close();
        }
    });
}

Network::Network(asio::io_context &io_context, short port) : _acceptor(io_context, tcp::endpoint(tcp::v4(), port)), _client_counter(0)
{
    acceptConnection();
}

void Network::acceptConnection()
{
    _acceptor.async_accept([this](std::error_code ec, tcp::socket socket) {
        if (!ec) {
            int client_number = ++_client_counter;
            std::make_shared<TCPCommunication>(std::move(socket), client_number)->start();
        } else {
            std::cerr << "Erreur d'acceptation: " << ec.message() << std::endl;
        }
        acceptConnection();
    });
}

int main(int ac, char **av)
{
    try {
        asio::io_context io_context;
        Network network(io_context, std::atoi(av[1]));
        io_context.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
