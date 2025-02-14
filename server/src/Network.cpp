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

rtype::server::Network::Network(int port)
    : _port(port), _running(true), _udpPort(DEFAULT_UDP_PORT), _context(),
      _acceptor(_context, TCP::endpoint(TCP::v4(), port))
{
}

int rtype::server::Network::run()
{
    return start();
}

int rtype::server::Network::start()
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
        TCP::socket socket = _acceptor.accept();
        _threads.push_back(std::thread(&Network::runClient, this, std::move(socket)));
    }

    for (auto &thread : _threads) {
        thread.join();
    }
}

void rtype::server::Network::runClient(TCP::socket socket)
{
    static unsigned int index = 0;

    asio::write(socket, asio::buffer("Welcome!\n"));

    unsigned int id = generateClientId(socket.local_endpoint()) + index;

    index += 1;

    TCPConnection client(std::move(socket), id, _lobbies, _udpPort++);

    client.start();
}
