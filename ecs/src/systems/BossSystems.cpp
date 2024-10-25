/*
** EPITECH PROJECT, 2024
** r type
** File description:
** boss sytem file
*/

#include <memory>

#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Life.hpp"
#include "Components/Position.hpp"
#include "IContext.hpp"
#include "Registry.hpp"
#include "Systems/BossSystems.hpp"
#include "ZipperIterator.hpp"

namespace ecs::systems {
    BossSystems::BossSystems(const nlohmann::json &config)
    {
        _bossLife = config["boss_life"];
        _bossSpeed = config["boss_speed"];
        _bossProjectileSpeed = config["boss_projectile_speed"];
        _movingProjectileSpeed = config["moving_projectile_speed"];
        _bossConfig = config["config_boss"];
        _projectileConfig = config["config_projectile"];
        _bossProjectileSpawnTime = config["boss_projectile_spawn_time"];
        _bossShootingElapsedTime = config["boss_shooting_elapsed_time"];
        _projectileClose = config["projectile_close"];
        _projectilePadding = config["projectile_padding"];
        _bossSpawnTime = config["boss_spawn_time"];
        _bossProjectileSpeed = config["boss_projectile_speed"];
        _bossMaxX = config["boss_max_x"];
    }

    void BossSystems::operator()(
        std::shared_ptr<Registry> &r,
        std::shared_ptr<ecs::IContext> ctx,
        ComponentFactory &factory
    )
    {
        bool isBoss = isABoss(r);

        if (_bossClock.getSeconds() < _bossSpawnTime && !isBoss) {
            return;
        }
        if (!isBoss && times < _bosses.size()) {
            auto createBossFunction = _bosses[times];
            createBossFunction(r, ctx, factory);
            times += 1;
        }

        auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();
        auto &positions = r->register_if_not_exist<ecs::component::Position>();
        auto &controllables = r->register_if_not_exist<ecs::component::Controllable>();
        auto &animations = r->register_if_not_exist<ecs::component::Animations>();
        auto &lifes = r->register_if_not_exist<ecs::component::Life>();
        auto &destroyables = r->register_if_not_exist<ecs::component::Destroyable>();
        auto &atr = r->register_if_not_exist<ecs::component::Attributes>();
        int idx = 0;

        for (auto &&[atr, pos, control, anim, life, destroyable] :
             custom_zip(attributes, positions, controllables, animations, lifes, destroyables)) {
            if (!atr || !pos || !control || !anim || !life || !destroyable ||
                destroyable->_state != ecs::component::Destroyable::DestroyState::ALIVE) {
                idx += 1;
                continue;
            }

            if (atr->_secondary_type != ecs::component::Attributes::SecondaryType::Boss) {
                idx += 1;
                continue;
            }

            if (atr->_entity_type == ecs::component::Attributes::EntityType::Weapon &&
                _projectileClock.getSeconds() > _movingProjectileSpeed) {
                moveProjectileTowardsPlayer(r, *pos, idx, ctx);
                _projectileClock.restart();
                continue;
            }

            if (_shootingClock.getSeconds() > _bossProjectileSpawnTime) {
                createNewProjectile(r, *pos, ctx, factory);
                _shootingClock.restart();
            }

            if (life->_life <= 0) {
                destroyable->_state = component::Destroyable::DestroyState::WAITING;
                break;
            }

            if (anim->_clock.getMiliSeconds() > 10 && pos->_x >= _bossMaxX) {
                pos->_x -= control->_speed;
                anim->_clock.restart();
            }
            idx += 1;
        }
    }

    void BossSystems::createNewProjectile(
        std::shared_ptr<Registry> &r,
        const ecs::component::Position &bossPos,
        std::shared_ptr<IContext> ctx,
        ComponentFactory &factory
    )
    {
        Entity newProjectile = factory.createEntity(r, _projectileConfig);
        auto &positions = r->register_if_not_exist<ecs::component::Position>();

        positions[newProjectile.getId()] = ecs::component::Position{bossPos._x, bossPos._y, false};
        ctx->createBossProjectile(newProjectile.getId(), rtype::protocol::BULLET);
    }

    void BossSystems::createFirstBoss(
        std::shared_ptr<Registry> &r,
        std::shared_ptr<IContext> ctx,
        ComponentFactory &factory
    )
    {
        Entity bossEntity = factory.createEntity(r, _bossConfig);

        ctx->createBoss(bossEntity.getId());
    }

    bool BossSystems::isABoss(std::shared_ptr<Registry> &r)
    {
        auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();

        for (auto &&[atr] : custom_zip(attributes)) {
            if (!atr) {
                continue;
            }
            if (atr->_secondary_type == ecs::component::Attributes::SecondaryType::Boss) {
                return true;
            }
        }

        return false;
    }

    void BossSystems::moveProjectileTowardsPlayer(
        std::shared_ptr<Registry> &r,
        ecs::component::Position &projectilePos,
        const std::size_t &idx,
        std::shared_ptr<IContext> ctx
    )
    {
        auto &positions = r->register_if_not_exist<ecs::component::Position>();
        ecs::component::Position playerPos = {0, 0};

        for (std::size_t i = 0; i < positions.size(); ++i) {
            if (positions[i] &&
                r->register_if_not_exist<ecs::component::Attributes>()[i]->_entity_type ==
                    ecs::component::Attributes::EntityType::Player) {
                playerPos._x = positions[i]->_x;
                playerPos._y = positions[i]->_y;
                break;
            }
        }

        if (playerPos._x == 0.0 && playerPos._y == 0.0) {
            return;
        }

        float distance =
            std::sqrt(std::pow(projectilePos._x - playerPos._x, 2) + std::pow(projectilePos._y - playerPos._y, 2));

        if (distance <= _projectileClose) {
            auto &destroyables = r->register_if_not_exist<ecs::component::Destroyable>();

            destroyables[idx]->_state = component::Destroyable::DestroyState::WAITING;
            return;
        }

        int targetX = playerPos._x;
        int targetY = playerPos._y;

        if (projectilePos._x < targetX) {
            projectilePos._x += _bossProjectileSpeed;
        } else if (projectilePos._x > targetX) {
            projectilePos._x -= _bossProjectileSpeed;
        }

        if (projectilePos._y < targetY) {
            projectilePos._y += _bossProjectileSpeed;
        } else if (projectilePos._y > targetY) {
            projectilePos._y -= _bossProjectileSpeed;
        }
    }
} // namespace ecs::systems
