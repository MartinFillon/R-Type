/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include "Game.hpp"
#include <string>
#include "protocol.hpp"

namespace Rtype {

    Game::Game() : _r(std::make_shared<ecs::Registry>()), _cf(_r) {}

    void Game::update() {}

    void Game::handleLeaving(const unsigned int id)
    {
        _r->_entities.erase(id);
    }

    void Game::createPlayer(const unsigned int id)
    {
        std::string file = "config/player";

        file.append(std::to_string(id));
        file.append(".json");

        ecs::Entity e = _cf.createEntity(file);

        _players[id] = ecs::Entity(e);
        _packetsToSend.push(Packet(protocol::NEW_PLAYER, {static_cast<uint8_t>(id)}));
    }

} // namespace Rtype
