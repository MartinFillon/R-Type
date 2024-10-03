/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Server
*/

#include "Server.hpp"
#include <cstdint>
#include <optional>
#include <queue>

namespace Rtype {

    Server::Server(int port)
        : _context(), _port(port), _running(true), _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
    {
        for (int i = 1; i < 5; i++) {
            _playerIds[i] = std::nullopt;
        }
    };

    int Server::run()
    {
        this->start();

        return EXIT_SUCCESS;
    }

    void Server::start()
    {
        std::cout << SERVER_START(_port) << std::endl;

        std::thread context([&]() { _context.run(); });

        std::thread acceptConnections(&Server::acceptConnections, this);
        std::thread processGame(&Server::processGame, this);

        context.detach();

        acceptConnections.join();
        processGame.join();
    }

    void Server::stop()
    {
        _running = false;
        _socket.close();

        std::cout << SERVER_STOP << std::endl;
    }

    void Server::broadcast(const Packet &packet)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        if (!packet.isValid()) {
            return;
        }

        for (const auto &client : _clients) {
            sendToClient(client.first, packet);
        }
    }

    void Server::handleMessage(const unsigned int id, const Message &message)
    {
        Packet packet(message);

        std::cout << MESSAGE_RECEIVED(id) << std::endl;

        processAction(id, packet);
    }

    int Server::placeInPlayers(void)
    {
        for (int i = 1; i < 5; i++) {
            if (_playerIds[i] == std::nullopt) {
                return i;
            }
        }

        return -1;
    }

    void Server::acceptConnections()
    {
        while (_running) {

            Endpoint endpoint;
            asio::error_code error;

            Message message(DATA_MAX_SIZE);

            std::lock_guard<std::mutex> lock(_mutex);

            size_t len = _socket.receive_from(asio::buffer(message), endpoint, 0, error);

            unsigned int id = generateClientId(endpoint);
            int place = placeInPlayers();

            std::cerr << error << " " << len << " " << place << std::endl;
            if (!error && len && place != -1) {

                if (_clients.find(id) == _clients.end()) {
                    _clients[id] = std::make_shared<Rtype::Client>(id, *this, endpoint, _socket);
                    _playerIds[place] = id;

                    _game.createPlayer(place);
                    _clients[id].get()->send(Packet(10, {static_cast<uint8_t>(id)}));
                }

                handleMessage(id, message);
            }

            if (error && _clients.find(id) != _clients.end()) {
                _clients[id].get()->disconnect();
            }
        }
    }

    void Server::processGame()
    {
        while (_running) {
            _game.update();
            std::queue<Packet> packets = _game.getPacketsToSend();
            while (!packets.empty()) {
                broadcast(packets.front());
                packets.pop();
            }
        }
    }

    void Server::sendToClient(const unsigned int id, const Packet &packet)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        if (!packet.isValid()) {
            return;
        }

        if (_clients.find(id) != _clients.end()) {
            _clients[id]->send(packet);
        }
    }

    void Server::removeClient(const unsigned int id)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        _clients.erase(id);
    }

    unsigned int Server::generateClientId(const Endpoint &endpoint)
    {
        std::hash<std::string> hashFunction;

        std::string id = endpoint.address().to_string() + std::to_string(endpoint.port());

        return static_cast<unsigned int>(hashFunction(id));
    }

    std::vector<uint8_t> Server::getBitshiftedData(const unsigned int data)
    {
        std::vector<uint8_t> bytes;

        bytes[0] = (data >> 24) & 0xFF;
        bytes[1] = (data >> 16) & 0xFF;
        bytes[2] = (data >> 8) & 0xFF;
        bytes[3] = data & 0xFF;

        return bytes;
    }

    void Server::processAction(const unsigned int id, const Packet &packet)
    {
        if (!packet.isValid()) {
            std::cout << INVALID_PACKET(id) << std::endl;
            return;
        }

        const int8_t optCode = packet.getOpcode();

        if (optCode == protocol::EVENT) {
            std::cout << "EVT\n";
            handleEvents(id, packet);
        }
        if (optCode == protocol::LEAVING) {
            std::cout << "LEAV\n";
            Packet brPacket(protocol::LEFT, getBitshiftedData(id));

            removeClient(id);
            _game.handleLeaving(id);
            broadcast(brPacket);
        }
        if (optCode == protocol::READY) {
            std::cout << "READ\n";
            // who asked and who cares??
        }
        if (optCode == protocol::PING) {
            std::cout << "PONG\n";
            Packet clPacket(protocol::PING);

            sendToClient(id, clPacket);
        }

        std::cout << packet.toMessage().data() << std::endl;

        std::cout << VALID_PACKET(id) << std::endl;
    }

    void Server::handleEvents(const unsigned int id, const Packet &packet)
    {
        // missing events ids and arguments in Notion protocol
    }
} // namespace Rtype
