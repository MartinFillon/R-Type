/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Server
*/

#include "Server.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>
#include "Components/Animations.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "IContext.hpp"
#include "Protocol.hpp"

rtype::Server::Server(int port)
    : _context(), _port(port), _running(true), _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
    _socket.non_blocking(true);

    for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++) {
        _players_clients_ids[player_place] = std::nullopt;
    }
};

int rtype::Server::run(std::shared_ptr<ecs::IContext> &context)
{
    start(context);

    return EXIT_SUCCESS;
}

void rtype::Server::start(std::shared_ptr<ecs::IContext> &ctx)
{
    std::cout << SERVER_START(_port) << std::endl;

    std::thread context([&]() { _context.run(); });

    std::thread acceptConnections(&Server::acceptConnections, this);
    std::thread processGame(&Server::processGame, this, ctx);

    context.detach();

    acceptConnections.join();
    processGame.join();
}

void rtype::Server::stop(void)
{
    _running = false;
    _socket.close();

    std::cout << SERVER_STOP << std::endl;
}

void rtype::Server::broadcast(const ecs::Packet &packet)
{
    if (!packet.isValid()) {
        return;
    }

    for (const auto &client : _clients) {
        sendToClient(client.first, packet);
    }
}

void rtype::Server::broadcastExcept(const unsigned int client_id, const ecs::Packet &packet)
{
    if (!packet.isValid()) {
        return;
    }

    for (const auto &client : _clients) {
        if (client.first != client_id) {
            sendToClient(client.first, packet);
        }
    }
}

void rtype::Server::handleMessage(const unsigned int client_id, const Message &message)
{
    ecs::Packet packet(message);

    std::cout << MESSAGE_RECEIVED(client_id) << std::endl;

    processAction(client_id, packet);
}

int rtype::Server::placeInPlayers(void)
{
    for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++) {
        if (_players_clients_ids[player_place] == std::nullopt) {
            return player_place;
        }
    }

    return -1;
}

int rtype::Server::getPlayerPlace(int client_id)
{
    for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++)
        if (_players_clients_ids[player_place] == client_id)
            return player_place;

    return -1;
}

int rtype::Server::countCurrentPlayer()
{
    int count = 0;

    for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++) {
        if (_players_clients_ids[player_place] != std::nullopt) {
            count += 1;
        }
    }

    return count;
}

void rtype::Server::acceptConnections(void)
{
    while (_running) {

        Endpoint endpoint;
        asio::error_code error;

        Message message(DATA_MAX_SIZE);

        std::lock_guard<std::mutex> lock(_mutex);

        std::size_t len = _socket.receive_from(asio::buffer(message), endpoint, 0, error);

        unsigned int client_id = generateClientId(endpoint);
        int player_place = placeInPlayers();

        if (!error && len && player_place != -1) {

            if (_clients.find(client_id) == _clients.end()) {
                _clients[client_id] = std::make_shared<rtype::Client>(client_id, *this, endpoint, _socket);
                _players_clients_ids[player_place] = client_id;
            }

            if (_clients[client_id]->isRunning()) {
                handleMessage(client_id, message);
            }
        }

        if (_clients.find(client_id) == _clients.end() && player_place == -1) {
            sendToClient(client_id, ecs::Packet(protocol::Operations::REFUSED));
        }

        if (error && _clients.find(client_id) != _clients.end()) {
            disconnectClient(client_id);
        }

        for (auto client : _clients) {
            if (!client.second->isRunning()) {
                continue;
            }
            if (client.second->getHeartbeatClock().getSeconds() > KEEPALIVE_TIMEOUT) {
                disconnectClient(client.first);
            }
        }
    }
}

void rtype::Server::disconnectClient(const unsigned int client_id)
{
    for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++) {
        if (_players_clients_ids[player_place] == client_id) {
            _players_clients_ids[player_place] = std::nullopt;
        }
    }

    _clients[client_id]->disconnect();

    removeClient(client_id);
}

void rtype::Server::processGame(std::shared_ptr<ecs::IContext> ctx)
{
    while (_running) {
        _game.update(_clients.size() > 0, ctx);

        std::vector<ecs::Packet> &packets = _game.getPacketsToSend();

        while (!packets.empty() && _clock.getSeconds() > FRAME_PER_SECONDS(5)) {
            broadcast(packets.front());
            packets.erase(packets.begin());
            _clock.restart();
        }
    }
}

void rtype::Server::sendToClient(const unsigned int client_id, const ecs::Packet &packet)
{
    if (!packet.isValid()) {
        return;
    }

    if (_clients.find(client_id) != _clients.end()) {
        _clients[client_id]->send(packet);
    }
}

void rtype::Server::removeClient(const unsigned int client_id)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _clients.erase(client_id);
}

unsigned int rtype::Server::generateClientId(const Endpoint &endpoint)
{
    std::hash<std::string> hashFunction;

    std::string id = endpoint.address().to_string() + std::to_string(endpoint.port());

    return static_cast<unsigned int>(hashFunction(id));
}

std::vector<uint8_t> rtype::Server::getBitshiftedData(const int length, const unsigned int data)
{
    std::vector<uint8_t> bytes;

    for (int index = 0; index < length; index++)
        bytes[index] = (data >> (length - (index + 1))) & 0xFF;

    return bytes;
}

void rtype::Server::processAction(const unsigned int client_id, const ecs::Packet &packet)
{
    if (!packet.isValid()) {
        std::cout << INVALID_PACKET(client_id) << std::endl;
        return;
    }

    const int8_t optCode = packet.getOpcode();

    if (optCode == protocol::Operations::EVENT) {
        handleEvents(client_id, packet);
        return;
    }

    if (optCode == protocol::Operations::LEAVING) {
        const ecs::Packet brPacket(protocol::Direction::LEFT, getBitshiftedData(4, client_id));
        const int player_place = getPlayerPlace(client_id);

        if (player_place > 0) {
            _game.handleLeaving(player_place);
            _players_clients_ids[player_place] = std::nullopt;
        }

        removeClient(client_id);
        broadcast(brPacket);
        return;
    }

    if (optCode == protocol::Operations::READY) {

        const unsigned int id = placeInPlayers();
        ecs::Entity e = _game.createPlayer(id);

        auto r = _game.getRegistry();
        auto &positions = r->get_components<ecs::component::Position>();
        auto &animations = r->get_components<ecs::component::Animations>();
        auto &drawables = r->get_components<ecs::component::Drawable>();
        auto &sprites = r->get_components<ecs::component::Sprite>();
        auto &sizes = r->get_components<ecs::component::Size>();

        for (std::size_t i = 0; i < r->_entities.size(); ++i) {
            if (!positions[i] || !animations[i] || !drawables[i] || !sprites[i] || !sizes[i]) {
                continue;
            }

            // if (animations[i]->_object == ecs::component::Object::Ennemies) {
            //     std::cerr << "Sending ennemy entity id: " << i << std::endl;
            //     sendToClient(
            //         client_id,
            //         ecs::Packet(
            //             protocol::NEW_OBJECT,
            //             {static_cast<uint8_t>(i), static_cast<uint8_t>(protocol::ObjectTypes::ENEMY)}
            //         )
            //     );
            // }

            if (animations[i]->_object == ecs::component::Object::Player) {
                std::cerr << "Player entity id: " << i << std::endl;
                sendToClient(
                    client_id,
                    ecs::Packet(
                        protocol::NEW_PLAYER,
                        {static_cast<uint8_t>(i),
                         static_cast<uint8_t>(static_cast<protocol::ObjectTypes>(_game.getEntityById(i)))}
                    )
                );
            }
        }
        _clients[client_id].get()->send(ecs::Packet(protocol::Operations::WELCOME, {static_cast<uint8_t>(id)}));
        broadcastExcept(
            client_id,
            ecs::Packet(protocol::Operations::NEW_PLAYER, {static_cast<uint8_t>(e.getId()), static_cast<uint8_t>(id)})
        );
        return;
    }

    if (optCode == protocol::Operations::PING) {

        if (_clients.find(client_id) != _clients.end()) {
            _clients[client_id]->getHeartbeatClock().restart();
        }

        const ecs::Packet clPacket(protocol::Operations::PING, {});

        sendToClient(client_id, clPacket);

        return;
    }

    std::cout << VALID_PACKET(client_id) << std::endl;
}

void rtype::Server::handleEvents(const unsigned int client_id, const ecs::Packet &packet)
{
    uint8_t event = packet.getArguments()[0];
    int player_place = -1;

    for (int i = FIRST_PLAYER_PLACE; i <= MAX_PLAYER_PLACES; ++i) {
        if (_players_clients_ids[i] == client_id) {
            player_place = i;
            break;
        }
    }

    if (event == protocol::Events::MOVE) {
        const uint8_t dir = packet.getArguments()[1];
        _game.movePlayer(player_place + 1, dir);
    }

    if (event == protocol::Events::SHOOT) {
        const int player_place = getPlayerPlace(client_id);

        if (player_place > 0) {
            _game.makePlayerShoot(player_place);
        }
    }
}
