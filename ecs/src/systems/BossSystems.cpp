/*
** EPITECH PROJECT, 2024
** r type
** File description:
** boss sytem file
*/

#include "Systems/BossSystems.hpp"
#include <iostream>
#include <memory>
#include "Components/Animations.hpp"
#include "Components/Life.hpp"
#include "IContext.hpp"
#include "Packet.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::BossSystems::operator()(Registry &r, std::shared_ptr<ecs::IContext> ctx)
{
    bool isBoss = isABoss(r);

    if (_bossClock.getSeconds() < BOSS_SPAWN_TIME && !isBoss) {
        return;
    }
    if (!isBoss && times < _bosses.size()) {
        auto createBossFunction = _bosses[times];
        createBossFunction(r, ctx);
        times += 1;
    }

    auto &positions = r.get_components<ecs::component::Position>();
    auto &controllables = r.get_components<ecs::component::Controllable>();
    auto &animations = r.get_components<ecs::component::Animations>();
    auto &lifes = r.get_components<ecs::component::Life>();
    auto &destroyables = r.get_components<ecs::component::Destroyable>();
    int idx = 0;

    for (auto &&[pos, control, anim, life, destroyable] :
         custom_zip(positions, controllables, animations, lifes, destroyables)) {
        if (!pos || !control || !anim || !life || !destroyable) {
            idx += 1;
            continue;
        }

        if (anim->_type != ecs::component::Type::Boss) {
            idx += 1;
            continue;
        }

        if (anim->_object == ecs::component::Weapon && _projectileClock.getSeconds() > MOVING_PROJECTILE_SPEED) {
            moveProjectileTowardsPlayer(r, *pos, idx, ctx);
            _projectileClock.restart();
            continue;
        }

        if (_shootingClock.getSeconds() > BOSS_PROJECTILE_SPAWN_TIME) {
            createNewProjectile(r, *pos, ctx);
            _shootingClock.restart();
        }

        if (life->_life <= 0) {
            destroyable->_destroyable = true;
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
    Registry &r,
    const ecs::component::Position &bossPos,
    std::shared_ptr<IContext> ctx
)
{
    Entity newProjectile = r.spawn_entity();
    r._entities.addEntity(newProjectile);
    auto &positions = r.get_components<ecs::component::Position>();
    auto &drawables = r.get_components<ecs::component::Drawable>();
    auto &controllables = r.get_components<ecs::component::Controllable>();
    auto &sprites = r.get_components<ecs::component::Sprite>();
    auto &animations = r.get_components<ecs::component::Animations>();
    auto &sizes = r.get_components<ecs::component::Size>();
    auto &destroyable = r.get_components<ecs::component::Destroyable>();
    auto &life = r.get_components<ecs::component::Life>();

    life[newProjectile.getId()] = ecs::component::Life{1};
    positions[newProjectile.getId()] = ecs::component::Position{bossPos._x, bossPos._y, false};
    drawables[newProjectile.getId()] = ecs::component::Drawable{true};
    controllables[newProjectile.getId()] = ecs::component::Controllable{true, BOSS_PROJECTILE_SPEED};
    sprites[newProjectile.getId()] = ecs::component::Sprite{ENNEMIES_WEAPON_SPRITE};
    destroyable[newProjectile.getId()] = ecs::component::Destroyable{false};
    animations[newProjectile.getId()] = ecs::component::Animations{
        ecs::Clock(), 20, 18, 0, 0, 0, ecs::component::Object::Weapon, ecs::component::Type::Boss
    };
    sizes[newProjectile.getId()] = ecs::component::Size{3, 3};
    ctx->createBossProjectile(newProjectile.getId(), rtype::protocol::BULLET);
}

void ecs::systems::BossSystems::createFirstBoss(Registry &r, std::shared_ptr<IContext> ctx)
{
    Entity bossEntity = r.spawn_entity();
    r._entities.addEntity(bossEntity);

    auto &positions = r.get_components<ecs::component::Position>();
    auto &drawables = r.get_components<ecs::component::Drawable>();
    auto &controllables = r.get_components<ecs::component::Controllable>();
    auto &sprites = r.get_components<ecs::component::Sprite>();
    auto &animations = r.get_components<ecs::component::Animations>();
    auto &sizes = r.get_components<ecs::component::Size>();
    auto &destroyable = r.get_components<ecs::component::Destroyable>();
    auto &life = r.get_components<ecs::component::Life>();

    positions[bossEntity.getId()] = ecs::component::Position{2000, 1080 - 127 * 4, false};
    drawables[bossEntity.getId()] = ecs::component::Drawable{true};
    controllables[bossEntity.getId()] = ecs::component::Controllable{false, BOSS_SPEED};
    sprites[bossEntity.getId()] = ecs::component::Sprite{FIRST_BOSS_SPRITE};
    animations[bossEntity.getId()] = ecs::component::Animations{
        Clock(), 255, 127, 260, 0, 0, ecs::component::Object::Ennemies, ecs::component::Type::Boss
    };
    sizes[bossEntity.getId()] = ecs::component::Size{4, 4};
    destroyable[bossEntity.getId()] = ecs::component::Destroyable{false};
    life[bossEntity.getId()] = ecs::component::Life{BOSS_LIFE(1)};
    ctx->createBoss(bossEntity.getId());
}

bool ecs::systems::BossSystems::isABoss(Registry &r)
{
    auto &animations = r.get_components<ecs::component::Animations>();

    for (auto &&[anim] : custom_zip(animations)) {
        if (!anim) {
            continue;
        }
        if (anim->_object == ecs::component::Object::Ennemies && anim->_type == ecs::component::Type::Boss) {
            return true;
        }
    }

    return false;
}

void ecs::systems::BossSystems::moveProjectileTowardsPlayer(
    Registry &r,
    ecs::component::Position &projectilePos,
    const std::size_t &idx,
    std::shared_ptr<IContext> ctx
)
{
    auto &positions = r.get_components<ecs::component::Position>();
    ecs::component::Position playerPos = {0, 0};

    for (std::size_t i = 0; i < positions.size(); ++i) {
        if (positions[i] &&
            r.get_components<ecs::component::Animations>()[i]->_object == ecs::component::Object::Player) {
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
        auto &destroyables = r.get_components<ecs::component::Destroyable>();
        destroyables[idx]->_destroyable = true;
        ctx->destroyObject(idx);
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
