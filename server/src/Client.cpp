/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include "Client.hpp"
#include <iostream>
#include <string>
#include "Server.hpp"

namespace rtype::server {
    Client::Client(const unsigned int client_id, Server &server, const Endpoint &endpoint, Socket &socket)
        : _id(client_id), _running(true), _server(server), _socket(socket), _endpoint(endpoint)
    {
        std::cout << NEW_CLIENT(_id) << std::endl;
    };

    void Client::send(const ecs::IPacket &packet)
    {
        if (packet.isValid()) {
            _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
        }
        usleep(100);
    }

    void Client::disconnect()
    {
        std::cout << CLIENT_LEFT(_id) << std::endl;
        _running = false;
    }

    bool Client::isRunning()
    {
        return _running;
    }

    ecs::Clock &Client::getHeartbeatClock()
    {
        return _heartbeatClock;
    }
} // namespace rtype::server
