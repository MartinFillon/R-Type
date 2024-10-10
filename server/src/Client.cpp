/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include "Client.hpp"
#include "Server.hpp"

rtype::Client::Client(const unsigned int client_id, Server &server, const Endpoint &endpoint, Socket &socket)
    : _id(client_id), _running(true), _server(server), _socket(socket), _endpoint(endpoint)
{
    std::cout << NEW_CLIENT(_id) << std::endl;
};

void rtype::Client::send(const Packet &packet)
{
    //std::cerr << "Sending packet to client [" << _id << "]" << packet.isValid() << std::endl;
    if (packet.isValid()) {
        _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
    }
}

void rtype::Client::disconnect()
{
    std::cout << CLIENT_LEFT(_id) << std::endl;
    _running = false;
}

bool rtype::Client::isRunning()
{
    return _running;
}

ecs::Clock &rtype::Client::getHeartbeatClock()
{
    return _heartbeatClock;
}
