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
#include "Protocol.hpp"

rtype::Server::Server(int port)
    : _context(), _port(port), _running(true), _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
    _socket.non_blocking(true);

    for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++) {
        _players_clients_ids[player_place] = std::nullopt;
    }
};

int rtype::Server::run()
{
    this->start();

    return EXIT_SUCCESS;
}

void rtype::Server::start()
{
    std::cout << SERVER_START(_port) << std::endl;

    std::thread context([&]() { _context.run(); });

    std::thread acceptConnections(&Server::acceptConnections, this);
    std::thread processGame(&Server::processGame, this);

    context.detach();

    acceptConnections.join();
    processGame.join();
}

void rtype::Server::stop()
{
    _running = false;
    _socket.close();

    std::cout << SERVER_STOP << std::endl;
}

void rtype::Server::broadcast(const Packet &packet)
{
    std::lock_guard<std::mutex> lock(_mutex);

    if (!packet.isValid()) {
        return;
    }

    for (const auto &client : _clients) {
        sendToClient(client.first, packet);
    }
}

void rtype::Server::handleMessage(const unsigned int client_id, const Message &message)
{
    Packet packet(message);

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

void rtype::Server::acceptConnections()
{
    while (_running) {

        Endpoint endpoint;
        asio::error_code error;

        Message message(DATA_MAX_SIZE);

        std::lock_guard<std::mutex> lock(_mutex);

        size_t len = _socket.receive_from(asio::buffer(message), endpoint, 0, error);

        unsigned int client_id = generateClientId(endpoint);
        int player_place = placeInPlayers();

        if (!error && len && player_place != -1) {

            if (_clients.find(client_id) == _clients.end()) {
                _clients[client_id] = std::make_shared<rtype::Client>(client_id, *this, endpoint, _socket);
                _players_clients_ids[player_place] = client_id;

                _game.createPlayer(player_place);
                _clients[client_id].get()->send(
                    Packet(protocol::Operations::WELCOME, {static_cast<uint8_t>(player_place)})
                );
            }
            if (_clients[client_id]->isRunning())
                handleMessage(client_id, message);
        }

        if (error && _clients.find(client_id) != _clients.end()) {
            disconnectClient(client_id);
        }

        for (auto client : _clients) {
            if (!client.second->isRunning())
                continue;
            if (client.second->getHeartbeatClock().getSeconds() > KEEPALIVE_TIMEOUT)
                disconnectClient(client.first);
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

void rtype::Server::processGame()
{
    while (_running) {
        _game.update(_clients.size() > 0 ? true : false);

        std::queue<Packet> &packets = _game.getPacketsToSend();

        while (!packets.empty()) {
            broadcast(packets.front());
            packets.pop();
            std::exit(0);
        }
    }
}

void rtype::Server::sendToClient(const unsigned int client_id, const Packet &packet)
{
    // std::lock_guard<std::mutex> lock(_mutex);

    if (!packet.isValid()) {
        return;
    }

    if (_clients.find(client_id) != _clients.end()) {
        std::cout << "Sent packet to client! Optcode: " << std::to_string(packet.getOpcode()) << std::endl;
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

void rtype::Server::processAction(const unsigned int client_id, const Packet &packet)
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
        std::cout << "READ\n";

        auto r = _game.getRegistry();
        auto &positions = r->get_components<ecs::component::Position>();
        auto &animations = r->get_components<ecs::component::Animations>();
        auto &drawables = r->get_components<ecs::component::Drawable>();
        auto &sprites = r->get_components<ecs::component::Sprite>();
        auto &sizes = r->get_components<ecs::component::Size>();
        int entity_id = 0;

        for (auto &&[draws, anim, sprite, size, pos] :
             ecs::custom_zip(drawables, animations, sprites, sizes, positions)) {
            if (!draws || !anim || !sprite || !size || !pos) {
                entity_id++;
                continue;
            }

            if (anim->_object == ecs::component::Object::Player) {
                for (int player_place = FIRST_PLAYER_PLACE; player_place < MAX_PLAYER_PLACES; player_place++) {
                    const int player_entity_id = _game.getPlayerEntityIdByPlace(player_place);

                    if (player_entity_id != entity_id) {
                        continue;
                    }
                    sendToClient(
                        client_id,
                        Packet(
                            protocol::NEW_OBJECT,
                            {static_cast<uint8_t>(entity_id),
                             static_cast<uint8_t>(static_cast<protocol::ObjectTypes>(player_place))}
                        )
                    );
                }
                entity_id++;
                continue;
            }
            if (anim->_object == ecs::component::Object::Weapon) {
                 sendToClient(
                    client_id,
                    Packet(
                        protocol::NEW_OBJECT,
                        {static_cast<uint8_t>(entity_id),
                        static_cast<uint8_t>(protocol::ObjectTypes::BULLET)}
                    )
                 );
            }
            entity_id++;
        }
        return;
    }
    if (optCode == protocol::Operations::PING) {
        std::cout << "PONG\n";

        if (_clients.find(client_id) != _clients.end()) {
            _clients[client_id]->getHeartbeatClock().restart();
        }

        const Packet clPacket(protocol::Operations::PING, {});

        sendToClient(client_id, clPacket);
        return;
    }

    std::cout << packet.toMessage().data() << std::endl;

    std::cout << VALID_PACKET(client_id) << std::endl;
}

void rtype::Server::handleEvents(const unsigned int client_id, const Packet &packet)
{
    uint8_t event = packet.getArguments()[0];
    int player_place = -1;

    for (int player_place = FIRST_PLAYER_PLACE; player_place <= MAX_PLAYER_PLACES; player_place++) {
        if (_players_clients_ids[player_place] == client_id) {
            player_place = player_place;
            break;
        }
    }

    if (event == protocol::Events::MOVE) {
        const uint8_t dir = packet.getArguments()[1];

        _game.movePlayer(player_place, dir);

        return;
    }
    if (event == protocol::Events::SHOOT) {
        const int player_place = getPlayerPlace(client_id);

        if (player_place > 0)
            _game.makePlayerShoot(player_place);

        return;
    }
}
