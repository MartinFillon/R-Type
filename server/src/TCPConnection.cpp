/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Network
*/

#include <iostream>

#include "TCPConnection.hpp"

rtype::server::TCPConnection::TCPConnection(TCP::socket socket, std::vector<std::shared_ptr<Lobby>> &lobbies): _socket(std::move(socket)), _lobbies(lobbies)
{
}

void rtype::server::TCPConnection::start()
{
    readClient();
}

void rtype::server::TCPConnection::setLobby(const std::string &lobby)
{
    _lobby = lobby;
}

void rtype::server::TCPConnection::readClient()
{
    auto self(shared_from_this());

    asio::async_read_until(
        _socket,
        asio::dynamic_buffer(_data),
        '\n',
        [this, self](std::error_code ec, std::size_t length) {

            if (!ec) {
                std::string message = _data.substr(0, length);

                if (message.find("Create")) {
                    _lobbies.push_back(std::make_shared<Lobby>("name"));
                    std::cout << "client has created a lobby\n";
                }
                std::cout << "from client #" << ": " << _data.substr(0, length) << std::endl;
                writeToClient(message);
            } else {
                std::cerr << ec.message() << std::endl;
            }

        }
    );
}

void rtype::server::TCPConnection::writeToClient(const std::string &message)
{
    auto self(shared_from_this());

    asio::async_write(_socket, asio::buffer(message + "\n"), [this, self](std::error_code ec, std::size_t) {
        if (!ec) {
            _data.clear();
            readClient();
        } else {
            std::cerr << "Erreur d'écriture: " << ec.message() << std::endl;
            _socket.close();
        }
    });
}
