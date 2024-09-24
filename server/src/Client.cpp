/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include "Client.hpp"

Rtype::Client::Client(const int id, Server *server, const Endpoint &endpoint, Socket &socket):
    _id(id),
    _running(true),
    _server(server),
    _socket(socket),
    _endpoint(endpoint)
{};

void Rtype::Client::run()
{
    while (_running) {
        listenToClient();
    }
}

void Rtype::Client::send(const Message &message)
{
    _socket.send_to(asio::buffer(message), _endpoint);
}

void Rtype::Client::disconnect()
{
    _running = false;
}

void Rtype::Client::listenToClient()
{
    try {

        asio::error_code error;

        Message data(DATA_MAX_SIZE);
        size_t len = _socket.receive_from(asio::buffer(data), _endpoint, 0, error);

        if (!error && len) {
            Message receivedData(data.begin(), data.begin() + len);
            //_server->handleMessage(_id, receivedData);
        }

    } catch (const std::exception& e) {
        disconnect();
    }

}