/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include <cstddef>
#include <memory>
#include <string>

#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "IContext.hpp"
#include "Protocol.hpp"
#include "Registry.hpp"
#include "Systems/BasicRandomEnnemiesSystem.hpp"
#include "Systems/BossSystems.hpp"
#include "Systems/CollisionsSystem.hpp"
#include "Systems/DestroySystem.hpp"
#include "Systems/EnnemiesMilepatesSystem.hpp"
#include "Systems/GunFireSystem.hpp"
#include "Systems/InvincibilitySystem.hpp"
#include "ZipperIterator.hpp"

namespace rtype::server {

    Game::Game() : _r(std::make_shared<ecs::Registry>()), _cf()
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
        int x = p->_x;
        int y = p->_y;

        _ctx->moveObject(entity_id, x, y);
    }

    void Game::update(bool are_any_clients_connected, std::shared_ptr<ecs::IContext> &ctx)
    {
        if (_ctx == nullptr) {
            _ctx = ctx;
        }
        auto &positions = _r->register_if_not_exist<ecs::component::Position>();
        auto &animations = _r->register_if_not_exist<ecs::component::Animations>();

        if (_systemClock.getSeconds() > FRAME_PER_SECONDS(20)) {
            _r->run_systems(_cf, ctx);
            _systemClock.restart();
        }

        for (std::size_t entity_id = 0; entity_id < positions.size(); entity_id++) {
            if (!positions[entity_id] || !animations[entity_id]) {
                continue;
            }
            if (are_any_clients_connected) {
                preparePosition(positions[entity_id], entity_id);
                _ctx->animationObject(entity_id, animations[entity_id].value());
            }
        }
    }

    void Game::handleLeaving(const unsigned int player_place)
    {
        _r->_entities.erase(_players_entities_ids[player_place]);
    }

    ecs::Entity Game::createPlayer(const unsigned int player_place)
    {
        std::string file = "./config/player";

        file.append(std::to_string(player_place));
        file.append(".json");

        ecs::Entity e = _cf.createEntity(_r, file);

        _players_entities_ids[player_place] = e.getId();

        return e;
    }

    void Game::movePlayer(const int player_place, const int dir)
    {
        const int player_entity_id = _players_entities_ids[player_place];

        auto &destroyable = _r->register_if_not_exist<ecs::component::Destroyable>()[player_entity_id];

        if (!destroyable || destroyable->_state != ecs::component::Destroyable::DestroyState::ALIVE) {
            return;
        }

        auto &position = _r->register_if_not_exist<ecs::component::Position>()[player_entity_id];
        auto &controllable = _r->register_if_not_exist<ecs::component::Controllable>()[player_entity_id];

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
        const int player_entity_id = _players_entities_ids[player_place];

        auto &destroyable = _r->register_if_not_exist<ecs::component::Destroyable>()[player_entity_id];

        if (!destroyable || destroyable->_state != ecs::component::Destroyable::DestroyState::ALIVE)
            return;

        auto &positions = _r->register_if_not_exist<ecs::component::Position>();
        auto &attributes = _r->register_if_not_exist<ecs::component::Attributes>();

        int i = 0;
        ecs::Entity e = _cf.createEntity(_r, CONFIG_PLAYER_PROJECTILE);
        _ctx->createProjectile(e.getId(), rtype::protocol::ObjectTypes::PLAYER_BULLET);

        for (auto &&[pos, atr] : ecs::custom_zip(positions, attributes)) {
            if (!pos || !atr) {
                i += 1;
                continue;
            }
            if (atr->_entity_type == ecs::component::Attributes::EntityType::Weapon &&
                atr->_secondary_type == ecs::component::Attributes::SecondaryType::None) {
                break;
            }
            i += 1;
        }

        positions[i] = positions[_players_entities_ids[player_place]];
        _ctx->createProjectile(i, rtype::protocol::ObjectTypes::PLAYER_BULLET);
        _ctx->moveObject(i, positions[i]->_x, positions[i]->_y);
    }

    void Game::setupDestroy()
    {
        _r->add_system(ecs::systems::DestroySystem());
    }

    void Game::setupCollisons()
    {
        _r->add_system(ecs::systems::CollisionsSystem());
        _r->add_system(ecs::systems::GunFireSystem());
        _r->add_system(ecs::systems::InvincibilitySystem());
    }

    void Game::setupBosses()
    {
        _r->add_system(ecs::systems::BossSystems());
    }

    void Game::setupBasicEnnemies()
    {
        _r->add_system(ecs::systems::EnnemiesMilepatesSystem());

        std::ifstream f("config/systems/basic_random_ennemies.json");
        nlohmann::json config = nlohmann::json::parse(f);

        _r->add_system(ecs::systems::BasicRandomEnnemiesSystem(config));
    }

    std::shared_ptr<ecs::Registry> Game::getRegistry()
    {
        return _r;
    }

    const int Game::getPlayerEntityIdByPlace(const int player_place)
    {
        return _players_entities_ids[player_place];
    }

    const int Game::getPlaceByPlayerEntityId(const int player_entity_id)
    {
        for (size_t i = 0; i < _players_entities_ids.size(); i++) {
            if (_players_entities_ids[i] == player_entity_id) {
                return i;
            }
        }
        return -1;
    }
} // namespace rtype::server
