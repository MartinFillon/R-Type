/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Network
*/

#include <cstdlib>
#include <iostream>
#include "TCPConnection.hpp"

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
    std::cout << NETWORK_START(_port) << std::endl;

    std::thread contextThread([&]() { _context.run(); });

    acceptConnection();
    contextThread.detach();

    return EXIT_SUCCESS;
}

unsigned int rtype::server::Network::generateClientId(const TCP::endpoint &endpoint)
{
        std::hash<std::string> hashFunction;

        std::string id = endpoint.address().to_string() + std::to_string(endpoint.port());

        return static_cast<unsigned int>(hashFunction(id));
}

void rtype::server::Network::acceptConnection()
{
    while (_running) {
        _acceptor.async_accept([this](std::error_code ec, TCP::socket socket) {
            if (!ec) {
                asio::write(socket, asio::buffer("Welcome!\n"), ec);
                unsigned int id = generateClientId(_acceptor.local_endpoint());
                std::make_shared<TCPConnection>(std::move(socket), id, _lobbies)->start();

            } else {
                std::cerr << "Erreur d'acceptation: " << ec.message() << std::endl;
            }
        });
    }
}