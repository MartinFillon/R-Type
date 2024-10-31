/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include <spdlog/spdlog.h>

#include "Client.hpp"
#include "Clock.hpp"
#include "Server.hpp"

namespace rtype::server {
    Client::Client(const unsigned int client_id, Server &server, const Endpoint &endpoint, Socket &socket)
        : _id(client_id), _running(true), _server(server), _socket(socket), _endpoint(endpoint)
    {
        spdlog::info("New client [{}] connected", _id);
    }

    void Client::send(const ecs::IPacket &packet)
    {
        if (packet.isValid()) {
            _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
        }
        ecs::Clock clock;
        while (clock.getMicroSeconds() < 200)
            ;
    }

    void Client::disconnect()
    {
        spdlog::info("Client [{}] disconnected", _id);
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
