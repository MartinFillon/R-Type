/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Network
*/

#include <cstdlib>
#include <iostream>

#include "Network.hpp"

rtype::server::Network::Network(int port): _port(port), _running(true), _context(), _acceptor(_context, TCP::endpoint(TCP::v4(), port))
{
}

int rtype::server::Network::run(std::shared_ptr<ecs::IContext> &context)
{
    return start(context);
}

int rtype::server::Network::start(std::shared_ptr<ecs::IContext> &context)
{
    std::cout << SERVER_START(_port) << std::endl;

    std::thread contextThread([&]() { _context.run(); });

    for (;;) {
        TCP::socket socket(_context);
        _acceptor.accept(socket);

        std::string message("Salut!");

        std::error_code error;
        asio:write(socket, asio::buffer(message), error);
    }

    contextThread.detach();

    return EXIT_SUCCESS;
}
