/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Server
*/

#include "Server.hpp"

Rtype::Server::Server(int port): 
    _context(),
    _port(port),
    _running(true),
    _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{};

void Rtype::Server::start()
{
    std::cout << SERVER_START(_port) << std::endl;

    std::thread context([&]() { _context.run(); });

    std::thread acceptConnections(&Rtype::Server::acceptConnections, this);
    std::thread processGame(&Rtype::Server::processGame, this);

    context.detach();

    acceptConnections.join();
    processGame.join();
}

void Rtype::Server::stop()
{
    _running = false;
    _socket.close();

    std::cout << SERVER_STOP << std::endl;
}

void Rtype::Server::broadcast(const Packet &packet)
{
    std::lock_guard<std::mutex> lock(_mutex);

    if (!packet.isValid()) {
        return;
    }

    for (const auto &client : _clients) {
        sendToClient(client.first, packet);
    }
}

void Rtype::Server::handleMessage(const int id, const Message &message)
{
    Packet packet(message);

    std::cout << MESSAGE_RECEIVED(id) << std::endl;

    _game.processAction(id, packet);
}

void Rtype::Server::acceptConnections()
{
    while (_running) {

        Endpoint endpoint;
        asio::error_code error;

        Message data(DATA_MAX_SIZE);

        size_t len = _socket.receive_from(asio::buffer(data), endpoint, 0, error);

        if (!error && len) {

            std::lock_guard<std::mutex> lock(_mutex);

            int id = generateClientId(endpoint);

            if (_clients.find(id) == _clients.end()) {
                _clients[id] = std::make_shared<Rtype::Client>(id, *this, endpoint, _socket);
                std::thread(&Rtype::Client::run, _clients[id]).detach();
            }
        }
    }
}

void Rtype::Server::processGame()
{
    while (_running) {
        _game.update();
    }
}

void Rtype::Server::sendToClient(const int id, const Packet &packet)
{
    std::lock_guard<std::mutex> lock(_mutex);

    if (!packet.isValid()) {
        return;
    }

    if (_clients.find(id) != _clients.end()) {
        _clients[id]->send(packet);
    }
}

void Rtype::Server::removeClient(const int id)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _clients.erase(id);
}

int Rtype::Server::generateClientId(const Endpoint &endpoint)
{
    std::hash<std::string> hashFunction;

    return static_cast<int>(hashFunction(endpoint.address().to_string() + std::to_string(endpoint.port())));
}
