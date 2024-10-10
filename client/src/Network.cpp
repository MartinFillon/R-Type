/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Network
*/

#include <iostream>
#include <stdexcept>

#include "Network.hpp"
#include "Protocol.hpp"

client::Network::Network(): _context(), _resolver(_context), _socket(_context) {}

void client::Network::setRegistry(std::shared_ptr<ecs::Registry> registry)
{
    _registry = registry;
}

int client::Network::setup(const std::string &host, const std::string &port)
{
    try {

        _endpoint = *_resolver.resolve(UDP::v4(), host, port).begin();
        _socket.open(UDP::v4());
        _socket.non_blocking(true);

    } catch (const std::runtime_error &e) {

        std::cerr << e.what() << std::endl;
        return ERROR;

    } catch (const std::exception &e) {

        std::cerr << e.what() << std::endl;
        return ERROR;

    }

    return SUCCESS;
}

int client::Network::run()
{
    bool running = true;

    std::thread context([&]() { _context.run(); });

    context.detach();

    send(rtype::Packet(protocol::Operations::READY));

    while (running) {

        Message message(DATA_MAX_SIZE);
        asio::error_code error;
        std::size_t len = _socket.receive_from(asio::buffer(message), _endpoint, 0, error);
        rtype::Packet received_packet(message);

        if (!error && len) {
            std::string str = "Received packet from server! Optcode: ";
            str += std::to_string(received_packet.getOpcode()) += "\n";
            if (!received_packet.getArguments().empty()) {
                if (received_packet.getArguments()[0]) {
                    str += "Arg0: ";
                    str += std::to_string(received_packet.getArguments()[0]) += "\n";
                }
                if (received_packet.getArguments()[1]) {
                    str += "Arg1: ";
                    str += std::to_string(received_packet.getArguments()[1]) += "\n";
                }
            }
            std::cout << str;
        }

        if (_keepaliveClock.getSeconds() > KEEPALIVE_TIMEOUT) {
            send(protocol::Operations::PING, {});
            _keepaliveClock.restart();
        }
    }

    return EXIT_SUCCESS;
}

void client::Network::send(const rtype::Packet &packet)
{
    if (!packet.isValid()) {
        std::cerr << "Packet is not valid" << std::endl;
        return;
    }

    _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
}

void client::Network::send(const uint8_t opcode, const Arguments &arguments)
{
    rtype::Packet packet(opcode, arguments);

    send(packet);
}
