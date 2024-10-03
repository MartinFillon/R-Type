/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include "Client.hpp"
#include "Server.hpp"

Rtype::Client::Client(const unsigned int id, Server &server, const Endpoint &endpoint, Socket &socket)
    : _id(id), _running(true), _server(server), _socket(socket), _endpoint(endpoint)
{
    std::cout << NEW_CLIENT(_id) << std::endl;
};

void Rtype::Client::send(const Packet &packet)
{
    std::cerr << "Sending packet to client [" << _id << "]" << packet.isValid() << std::endl;
    if (packet.isValid()) {
        _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
    }
}

void Rtype::Client::disconnect()
{
    std::cout << CLIENT_LEFT(_id) << std::endl;
    _running = false;
}
