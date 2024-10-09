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

    void Game::preparePosition(const std::optional<ecs::component::Position> &p, int entity_id)
    {
        std::vector<uint8_t> args;
        int x = p->_x;
        int y = p->_y;

        args.reserve(sizeof(int) + sizeof(int) + sizeof(int));
        for (size_t i = 0; i < sizeof(int); ++i) {
            args.push_back(entity_id & 0xFF);
            args.push_back(x & 0xFF);
            args.push_back(y & 0xFF);
            entity_id >>= 8;
            x >>= 8;
            y >>= 8;
        }

        _packetsToSend.push(Packet(protocol::Operations::OBJECT_POSITION, args));
    }

    void Game::update(bool are_any_clients_connected)
    {
        auto &position_array = _r->register_component<ecs::component::Position>();

        for (size_t entity_id = 0; entity_id < position_array.size(); entity_id++) {
            if (!position_array[entity_id])
                continue;
            if (are_any_clients_connected)
                preparePosition(position_array[entity_id], entity_id);
        }
    }

    void Game::handleLeaving(const unsigned int player_place)
    {
        _r->_entities.erase(_players_entities_ids[player_place]);
    }

    void Game::createPlayer(const unsigned int player_place)
    {
        std::string file = "config/player";

        file.append(std::to_string(player_place));
        file.append(".json");

        std::cerr << file << std::endl;
        ecs::Entity e = _cf.createEntity(file);

        _players_entities_ids[player_place] = e.getId();
        _packetsToSend.push(Packet(protocol::Operations::NEW_PLAYER, {static_cast<uint8_t>(player_place)}));
    }

    void Game::movePlayer(const int player_place, const int dir)
    {
        const int player_entity_id = _players_entities_ids[player_place];
        auto &position = _r->register_component<ecs::component::Position>()[player_entity_id];
        auto &controllable = _r->register_component<ecs::component::Controllable>()[player_entity_id];

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
    }

    void Game::makePlayerShoot(int player_place)
    {
        std::string file = "config/projectile";

        file.append(".json");

        ecs::Entity e = _cf.createEntity(file);
        auto &positions = _r->get_components<ecs::component::Position>();

        positions[e.getId()] = positions[_players_entities_ids[player_place]];
        _packetsToSend.push(Packet(
            protocol::Operations::NEW_OBJECT,
            {static_cast<uint8_t>(e.getId()), static_cast<uint8_t>(protocol::ObjectTypes::BULLET)}
        ));
    }

} // namespace Rtype
