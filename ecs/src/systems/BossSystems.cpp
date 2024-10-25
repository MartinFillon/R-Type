/*
** EPITECH PROJECT, 2024
** r type
** File description:
** boss sytem file
*/

#include "Systems/BossSystems.hpp"
#include <memory>
#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Life.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "IContext.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::BossSystems::operator()(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<ecs::IContext> ctx,
    ComponentFactory &factory
)
{
    bool isBoss = isABoss(r);

    if (_bossClock.getSeconds() < BOSS_SPAWN_TIME && !isBoss) {
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
    int idx = 0;

    for (auto &&[atr, pos, control, anim, life, destroyable] :
         custom_zip(attributes, positions, controllables, animations, lifes, destroyables)) {
        if (!atr || !pos || !control || !anim || !life || !destroyable ||
            destroyable->_state != ecs::component::Destroyable::DestroyState::ALIVE) {
            idx += 1;
            continue;
        }

        if (atr->_ennemy_type != ecs::component::Attributes::EnnemyType::Boss) {
            idx += 1;
            continue;
        }

        if (atr->_entity_type == ecs::component::Attributes::EntityType::Weapon &&
            _projectileClock.getSeconds() > MOVING_PROJECTILE_SPEED) {
            moveProjectileTowardsPlayer(r, *pos, idx, ctx);
            _projectileClock.restart();
            continue;
        }

        if (_shootingClock.getSeconds() > BOSS_PROJECTILE_SPAWN_TIME) {
            createNewProjectile(r, *pos, ctx, factory);
            _shootingClock.restart();
        }

        if (life->_life <= 0) {
            destroyable->_state = component::Destroyable::DestroyState::WAITING;
            break;
        }

        if (anim->_clock.getMiliSeconds() > 10 && pos->_x >= 1000) {
            pos->_x -= control->_speed;
            anim->_clock.restart();
        }
        idx += 1;
    }
}

void ecs::systems::BossSystems::createNewProjectile(
    std::shared_ptr<Registry> &r,
    const ecs::component::Position &bossPos,
    std::shared_ptr<IContext> ctx,
    ComponentFactory &factory
)
{
    Entity newProjectile = factory.createEntity(r, CONFIG_PROJECTILE);
    auto &positions = r->register_if_not_exist<ecs::component::Position>();

    positions[newProjectile.getId()] = ecs::component::Position{bossPos._x, bossPos._y, false};
    ctx->createBossProjectile(newProjectile.getId(), rtype::protocol::BULLET);
}

void ecs::systems::BossSystems::createFirstBoss(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<IContext> ctx,
    ComponentFactory &factory
)
{
    Entity bossEntity = factory.createEntity(r, CONFIG_BOSS);

    ctx->createBoss(bossEntity.getId());
}

bool ecs::systems::BossSystems::isABoss(std::shared_ptr<Registry> &r)
{
    auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();

    for (auto &&[atr] : custom_zip(attributes)) {
        if (!atr) {
            continue;
        }
        if (atr->_ennemy_type == ecs::component::Attributes::EnnemyType::Boss) {
            return true;
        }
    }

    return false;
}

void ecs::systems::BossSystems::moveProjectileTowardsPlayer(
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

    if (distance <= PROJECTILE_CLOSE) {
        auto &destroyables = r->register_if_not_exist<ecs::component::Destroyable>();

        destroyables[idx]->_state = component::Destroyable::DestroyState::WAITING;
        return;
    }

    int targetX = playerPos._x;
    int targetY = playerPos._y;

    if (projectilePos._x < targetX) {
        projectilePos._x += BOSS_PROJECTILE_SPEED;
    } else if (projectilePos._x > targetX) {
        projectilePos._x -= BOSS_PROJECTILE_SPEED;
    }

    if (projectilePos._y < targetY) {
        projectilePos._y += BOSS_PROJECTILE_SPEED;
    } else if (projectilePos._y > targetY) {
        projectilePos._y -= BOSS_PROJECTILE_SPEED;
    }
}
