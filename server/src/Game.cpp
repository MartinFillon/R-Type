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
#include "Protocol.hpp"

rtype::Game::Game() : _r(std::make_shared<ecs::Registry>()), _cf(_r, ecs::ComponentFactory::Mode::Client)
{
    _r->register_component<ecs::component::Position>();
    _r->register_component<ecs::component::Controllable>();
    _r->register_component<ecs::component::Animations>();
    _r->register_component<ecs::component::Size>();
    _r->register_component<ecs::component::Drawable>();
    _r->register_component<ecs::component::Sprite>();
    _r->register_component<ecs::component::Destroyable>();

    // setupBackground();
    setupBasicEnnemies();
    setupCollisons();
    setupDestroy();
    setupBosses();
}

void rtype::Game::preparePosition(const std::optional<ecs::component::Position> &p, int entity_id)
{
    std::vector<uint8_t> args;
    int x = p->_x;
    int y = p->_y;

    std::cerr << "pos: " << x << " y: " << y << "\n";

    args.push_back(entity_id);

    args.push_back(x >> 8);
    args.push_back(x & 0xFF);

    args.push_back(y >> 8);
    args.push_back(y & 0xFF);

    _packetsToSend.push_back(Packet(protocol::Operations::OBJECT_POSITION, args));
}

void rtype::Game::update(bool are_any_clients_connected)
{
    auto &positions = _r->get_components<ecs::component::Position>();

    if (_systemClock.getSeconds() > FRAME_PER_SECONDS(SERVER_TPS)) {
        _r->run_systems();
        _systemClock.restart();
    }

    for (std::size_t entity_id = 0; entity_id < positions.size(); entity_id++) {
        if (!positions[entity_id])
            continue;
        if (are_any_clients_connected)
            preparePosition(positions[entity_id], entity_id);
    }
}

void rtype::Game::handleLeaving(const unsigned int player_place)
{
    _r->_entities.erase(_players_entities_ids[player_place]);
}

void rtype::Game::createPlayer(const unsigned int player_place)
{
    std::string file = "config/player";

    file.append(std::to_string(player_place));
    file.append(".json");

    std::cerr << file << std::endl;
    ecs::Entity e = _cf.createEntity(file);

    _players_entities_ids[player_place] = e.getId();
    _packetsToSend.push_back(Packet(protocol::Operations::NEW_PLAYER, {static_cast<uint8_t>(player_place)}));
}

void rtype::Game::movePlayer(const int player_place, const int dir)
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

void rtype::Game::makePlayerShoot(int player_place)
{
    std::string file = "config/projectile";

    file.append(".json");

    ecs::Entity e = _cf.createEntity(file);
    auto &positions = _r->get_components<ecs::component::Position>();

    positions[e.getId()] = positions[_players_entities_ids[player_place]];
    _packetsToSend.push_back(Packet(
        protocol::Operations::NEW_OBJECT,
        {static_cast<uint8_t>(e.getId()), static_cast<uint8_t>(protocol::ObjectTypes::BULLET)}
    ));
}

void rtype::Game::setupDestroy()
{
    _r->add_system(ecs::systems::DestroySystem());
}

void rtype::Game::setupCollisons()
{
    // _r->add_system(ecs::systems::CollisionsSystem());
}

void rtype::Game::setupBosses()
{
    // _r->add_system(ecs::systems::BossSystems());
}

void rtype::Game::setupBasicEnnemies()
{
    // _r->add_system(ecs::systems::EnnemiesMilespatesSystem());
    // _r->add_system(ecs::systems::BasicRandomEnnemiesSystem());
}

void rtype::Game::setupBackground()
{
    _cf.createEntity("config/background/background.json");
    _cf.createEntity("config/background/background_2.json");
    _cf.createEntity("config/background/background_3.json");
    _cf.createEntity("config/background/background_4.json");
    _r->add_system(ecs::systems::ParalaxSystem());
}

std::shared_ptr<ecs::Registry> rtype::Game::getRegistry()
{
    return _r;
}

const int rtype::Game::getPlayerEntityIdByPlace(const int player_place)
{
    return _players_entities_ids[player_place];
}
