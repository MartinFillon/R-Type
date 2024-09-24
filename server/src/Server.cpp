/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Server
*/

#include "Server.hpp"

Rtype::Server::Server(int port): 
    _port(port),
    _socket(_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{};

void Rtype::Server::start()
{
    std::thread acceptConnections(&Rtype::Server::acceptConnections, this);
    std::thread processGame(&Rtype::Server::processGame, this);

    acceptConnections.join();
    processGame.join();
}

void Rtype::Server::stop()
{
    _running = false;
    _socket.close();
}

void Rtype::Server::broadcast(const Message &message)
{
    std::lock_guard<std::mutex> lock(_mutex);

    for (const auto &client : _clients) {
        sendToClient(client.first, message);
    }
}

void Rtype::Server::handleMessage(const int id, const Message &message)
{
    // Packet packet(message) //

    _game.processAction(); // Passer l'id du client et le packet //
}

void Rtype::Server::acceptConnections()
{
    while (_running) {

        Endpoint endpoint;
        std::vector<uint8_t> data(DATA_MAX_SIZE);
        asio::error_code error;

        size_t len = _socket.receive_from(asio::buffer(data), endpoint, 0, error);

        if (!error && len) {

            std::lock_guard<std::mutex> lock(_mutex);

            int id = generateClientId(endpoint);

            if (_clients.find(id) == _clients.end()) {
                _clients[id] = std::make_shared<Rtype::Client>(id, this, endpoint, _socket);
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

void Rtype::Server::sendToClient(const int id, const Message &message)
{
    std::lock_guard<std::mutex> lock(_mutex);

    if (_clients.find(id) != _clients.end()) {
        _clients[id]->send(message);
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
