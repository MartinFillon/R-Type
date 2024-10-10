/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Network
*/

#include "Network.hpp"
#include <iostream>
#include <stdexcept>
#include "Protocol.hpp"

rtype::Network::Network() : _context(), _resolver(_context), _socket(_context) {}

int rtype::Network::setup(const std::string host, const std::string port)
{
    try {
        _endpoint = *_resolver.resolve(UDP::v4(), host, port).begin();
        _socket.open(UDP::v4());
        _socket.non_blocking(true);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int rtype::Network::run()
{
    bool running = true;

    std::thread context([&]() { _context.run(); });

    context.detach();

    Packet ready_packet(protocol::Operations::READY, {}); // Ready message to server

    send(ready_packet);

    while (running) {

        Message message(DATA_MAX_SIZE);
        asio::error_code error;
        std::size_t len = _socket.receive_from(asio::buffer(message), _endpoint, 0, error);
        Packet received_packet(message);

        if (!error && len) {
            std::string str = "Received packet from server! Optcode: ";
            str += std::to_string(received_packet.getOpcode()) += "\n";
            if (!received_packet.getArguments().empty()) {
                if (received_packet.getArguments()[0])
                    str += "Arg0: ";
                str += std::to_string(received_packet.getArguments()[0]) += "\n";
                if (received_packet.getArguments()[1])
                    str += "Arg1: ";
                str += std::to_string(received_packet.getArguments()[1]) += "\n";
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

void rtype::Network::send(const Packet &packet)
{
    if (!packet.isValid()) {
        std::cerr << "Packet is not valid" << std::endl;
        return;
    }

    _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
}

void rtype::Network::send(const Message &message)
{
    Packet packet(message);

    send(packet);
}

void rtype::Network::send(const uint8_t opcode, const Arguments &arguments)
{
    Packet packet(opcode, arguments);

    send(packet);
}
