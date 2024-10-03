/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "ComponentFactory.hpp"
#include "Components/Controllable.hpp"
#include "Components/Position.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "Packet.hpp"
#include "protocol.hpp"

namespace Rtype {

    Game::Game() : _r(std::make_shared<ecs::Registry>()), _cf(_r, ecs::ComponentFactory::Mode::Server) {}

    void Game::preparePosition(const std::optional<ecs::component::Position> &p, int idx)
    {
        std::vector<uint8_t> args;
        int x = p->_x;
        int y = p->_y;

        args.reserve(sizeof(int) + sizeof(int) + sizeof(int));
        for (size_t i = 0; i < sizeof(int); ++i) {
            args.push_back(idx & 0xFF);
            args.push_back(x & 0xFF);
            args.push_back(y & 0xFF);
            idx >>= 8;
            x >>= 8;
            y >>= 8;
        }

        _packetsToSend.push(Packet(1, args));
    }

    void Game::update()
    {
        auto &position_array = _r->register_component<ecs::component::Position>();

        for (size_t i = 0; i < position_array.size(); i++) {
            if (!position_array[i])
                continue;
            preparePosition(position_array[i], i);
        }
    }

    void Game::handleLeaving(const unsigned int id)
    {
        _r->_entities.erase(id);
    }

    void Game::createPlayer(const unsigned int id)
    {
        std::string file = "config/player";

        file.append(std::to_string(id));
        file.append(".json");

        std::cerr << file << std::endl;
        ecs::Entity e = _cf.createEntity(file);

        _players[id] = e.getId();
        _packetsToSend.push(Packet(protocol::NEW_PLAYER, {static_cast<uint8_t>(id)}));
    }

    const std::optional<ecs::component::Position> Game::movePlayer(const int id, const int dir)
    {
        const int eid = _players[id];
        auto &position = _r->register_component<ecs::component::Position>()[id];
        auto &controllable = _r->register_component<ecs::component::Controllable>()[id];

        if (dir == protocol::Direction::UP) {
            position->_y -= controllable->_speed;
            // if (animation->_clock.getElapsedTime().asSeconds() > PLAYER_MOVE_ANIMATION && animation->_x < 135) {
            //     animation->_x += 35;
            //     animation->_clock.restart();
            // }
        }
        if (dir == protocol::Direction::DOWN) {
            position->_y += controllable->_speed;
            // if (animation->_clock.getElapsedTime().asSeconds() > PLAYER_MOVE_ANIMATION && animation->_x > 0) {
            //     animation->_x -= 35;
            //     animation->_clock.restart();
            // }
        }
        if (dir == protocol::Direction::LEFT) {
            position->_x -= controllable->_speed;
        }
        if (dir == protocol::Direction::RIGHT) {
            position->_x += controllable->_speed;
        }

        return position;
    }

} // namespace Rtype
