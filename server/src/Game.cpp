/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "ComponentFactory.hpp"
#include "Components/Controllable.hpp"
#include "Components/Position.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "Packet.hpp"
#include "Protocol.hpp"
#include "Systems/BasicRandomEnnemiesSystem.hpp"
#include "Systems/CollisionsSystem.hpp"
#include "Systems/DestroySystem.hpp"

namespace rtype::server {

    Game::Game() : _r(std::make_shared<ecs::Registry>()), _cf(_r, ecs::ComponentFactory::Mode::Client)
    {
        _r->register_component<ecs::component::Position>();
        _r->register_component<ecs::component::Controllable>();
        _r->register_component<ecs::component::Animations>();
        _r->register_component<ecs::component::Size>();
        _r->register_component<ecs::component::Drawable>();
        _r->register_component<ecs::component::Sprite>();
        _r->register_component<ecs::component::Destroyable>();

        setupBasicEnnemies();
        setupCollisons();
        setupDestroy();
        setupBosses();
    }

    void Game::preparePosition(const std::optional<ecs::component::Position> &p, int entity_id)
    {
        std::vector<uint8_t> args;

        int x = p->_x;
        int y = p->_y;

        args.push_back(entity_id);

        args.push_back(x >> 8);
        args.push_back(x & 0xFF);

        args.push_back(y >> 8);
        args.push_back(y & 0xFF);

        _packetsToSend.push_back(ecs::Packet(protocol::Operations::OBJECT_POSITION, args));
    }

    void Game::update(bool are_any_clients_connected, std::shared_ptr<ecs::IContext> &ctx)
    {
        auto &positions = _r->get_components<ecs::component::Position>();

        if (_systemClock.getSeconds() > FRAME_PER_SECONDS(20)) {
            _r->run_systems(ctx);
            _systemClock.restart();
        }

        for (std::size_t entity_id = 0; entity_id < positions.size(); entity_id++) {
            if (!positions[entity_id]) {
                continue;
            }
            if (are_any_clients_connected) {
                preparePosition(positions[entity_id], entity_id);
            }
        }
    }

    void Game::handleLeaving(const unsigned int player_place)
    {
        _r->_entities.erase(_players_entities_ids[player_place]);
    }

    ecs::Entity Game::createPlayer(const unsigned int player_place)
    {
        std::string file = "config/player";

        file.append(std::to_string(player_place));
        file.append(".json");

        std::cerr << file << std::endl;
        ecs::Entity e = _cf.createEntity(file);

        _players_entities_ids[player_place] = e.getId();

        return e;
    }

    void Game::movePlayer(const int player_place, const int dir)
    {
        const int player_entity_id = _players_entities_ids[player_place];

        auto &position = _r->get_components<ecs::component::Position>()[player_entity_id];
        auto &controllable = _r->get_components<ecs::component::Controllable>()[player_entity_id];

        if (dir == protocol::Direction::UP) {
            position->_y -= controllable->_speed;
        }
        if (dir == protocol::Direction::DOWN) {
            position->_y += controllable->_speed;
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
        ecs::Entity e = _cf.createEntity("config/projectile.json");
        auto &positions = _r->get_components<ecs::component::Position>();

        positions[e.getId()] = positions[_players_entities_ids[player_place]];
        _packetsToSend.push_back(ecs::Packet(
            protocol::Operations::NEW_OBJECT,
            {static_cast<uint8_t>(e.getId()), static_cast<uint8_t>(protocol::ObjectTypes::BULLET)}
        ));
    }

    void Game::setupDestroy()
    {
        _r->add_system(ecs::systems::DestroySystem());
    }

    void Game::setupCollisons()
    {
        _r->add_system(ecs::systems::CollisionsSystem());
    }

    void Game::setupBosses()
    {
        // _r->add_system(ecs::systems::BossSystems());
    }

    void Game::setupBasicEnnemies()
    {
        // _r->add_system(ecs::systems::EnnemiesMilespatesSystem());
        _r->add_system(ecs::systems::BasicRandomEnnemiesSystem());
    }

    std::shared_ptr<ecs::Registry> Game::getRegistry()
    {
        return _r;
    }

    const int Game::getPlayerEntityIdByPlace(const int player_place)
    {
        return _players_entities_ids[player_place];
    }

    const int Game::getEntityById(int id)
    {
        for (size_t i = 0; i < _players_entities_ids.size(); i++) {
            if (_players_entities_ids[i] == id) {
                return i;
            }
        }
        return -1;
    }
} // namespace rtype::server
