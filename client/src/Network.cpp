/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Network
*/

#include <iostream>

#include "Network.hpp"

rtype::Network::Network(const std::string &host, const std::string &port):
    _context(),
    _resolver(_context),
    _socket(_context)
{
    _endpoint = *_resolver.resolve(UDP::v4(), host, port).begin();
    _socket.open(UDP::v4());
};

void rtype::Network::run()
{
    bool running = true;

    std::thread context([&](){ _context.run(); });

    context.detach();

    Packet packet(12); // Ready message to server //

    _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);

    while (running) {

        Message message(DATA_MAX_SIZE);
        asio::error_code error;

        size_t len = _socket.receive_from(asio::buffer(message), _endpoint, 0, error);

        std::cout << "Packet recu du server!" << std::endl;

    }
}

void rtype::Network::send(const Packet &packet)
{
    if (!packet.isValid()) {
        return;
    }

    _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
}

void rtype::Network::send(const Message &message)
{
    Packet packet(message);

    if (!packet.isValid()) {
        return;
    }

    _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
}

void rtype::Network::send(const uint8_t opcode, const Arguments &arguments)
{
    Packet packet(opcode, arguments);

    if (!packet.isValid()) {
        return;
    }

    _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
}

void rtype::Network::setRegistry(std::shared_ptr<ecs::Registry> registry)
{
    _registry = registry;
}
