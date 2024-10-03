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
#include "protocol.hpp"

namespace Rtype {

    Server::Server(int port)
        : _context(), _port(port), _running(true), _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
    {
        for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++) {
            _players_clients_ids[player_place] = std::nullopt;
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

    void Server::handleMessage(const unsigned int client_id, const Message &message)
    {
        Packet packet(message);

        std::cout << MESSAGE_RECEIVED(client_id) << std::endl;

        processAction(client_id, packet);
    }

    int Server::placeInPlayers(void)
    {
        for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++) {
            if (_players_clients_ids[player_place] == std::nullopt) {
                return player_place;
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

            unsigned int client_id = generateClientId(endpoint);
            int player_place = placeInPlayers();

            std::cerr << error << " " << len << " " << player_place << std::endl;
            if (!error && len && player_place != -1) {

                if (_clients.find(client_id) == _clients.end()) {
                    _clients[client_id] = std::make_shared<Rtype::Client>(client_id, *this, endpoint, _socket);
                    _players_clients_ids[player_place] = client_id;

                    _game.createPlayer(player_place);
                    _clients[client_id].get()->send(Packet(10, {static_cast<uint8_t>(client_id)}));
                }

                handleMessage(client_id, message);
            }

            if (error && _clients.find(client_id) != _clients.end()) {
                _clients[client_id].get()->disconnect();
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

    void Server::sendToClient(const unsigned int client_id, const Packet &packet)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        if (!packet.isValid()) {
            return;
        }

        if (_clients.find(client_id) != _clients.end()) {
            _clients[client_id]->send(packet);
        }
    }

    void Server::removeClient(const unsigned int client_id)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        _clients.erase(client_id);
    }

    unsigned int Server::generateClientId(const Endpoint &endpoint)
    {
        std::hash<std::string> hashFunction;

        std::string id = endpoint.address().to_string() + std::to_string(endpoint.port());

        return static_cast<unsigned int>(hashFunction(id));
    }

    std::vector<uint8_t> Server::getBitshiftedData(const int length, const unsigned int data)
    {
        std::vector<uint8_t> bytes;

        for (int index = 0; index < length; index++)
            bytes[index] = (data >> (length - (index + 1))) & 0xFF;

        return bytes;
    }

    std::vector<uint8_t> concatVectors(std::vector<uint8_t> vec1, std::vector<uint8_t> vec2)
    {
        vec1.insert(vec1.end(), vec2.begin(), vec2.end());

        return vec1;
    }

    void Server::processAction(const unsigned int client_id, const Packet &packet)
    {
        if (!packet.isValid()) {
            std::cout << INVALID_PACKET(client_id) << std::endl;
            return;
        }

        const int8_t optCode = packet.getOpcode();

        if (optCode == protocol::Operations::EVENT) {
            std::cout << "EVT\n";
            handleEvents(client_id, packet);
            return;
        }
        if (optCode == protocol::Operations::LEAVING) {
            std::cout << "LEAV\n";
            const Packet brPacket(protocol::Direction::LEFT, getBitshiftedData(4, client_id));

            for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++)
                if (_players_clients_ids[player_place] == client_id) {
                    _game.handleLeaving(player_place);
                    _players_clients_ids[player_place] = std::nullopt;
                }

            removeClient(client_id);
            broadcast(brPacket);
            return;
        }
        if (optCode == protocol::Operations::READY) {
            std::cout << "READ\n";
            // who asked and who cares??
            return;
        }
        if (optCode == protocol::Operations::PING) {
            std::cout << "PONG\n";
            const Packet clPacket(protocol::Operations::PING);

            sendToClient(client_id, clPacket);
            return;
        }

        std::cout << packet.toMessage().data() << std::endl;

        std::cout << VALID_PACKET(client_id) << std::endl;
    }

    void Server::handleEvents(const unsigned int client_id, const Packet &packet)
    {
        uint8_t event = packet.getArguments()[0];
        int player_place = -1;

        for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++) {
            if (_players_clients_ids[player_place] == client_id) {
                player_place = player_place;
                break;
            }
        }

        if (event == protocol::Events::Move) {
            const uint8_t dir = packet.getArguments()[1];

            _game.movePlayer(player_place, dir);

            return;
        }
        if (event == protocol::Events::Shoot) {
            return;
        }
    }
} // namespace Rtype
