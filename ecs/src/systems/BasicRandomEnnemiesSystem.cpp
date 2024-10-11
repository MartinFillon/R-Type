/*
** EPITECH PROJECT, 2024
** ennemy moves system file
** File description:
** BasicRandomEnnemiesSystem
*/

#include "Systems/BasicRandomEnnemiesSystem.hpp"
#include <memory>
#include <random>
#include "Components/Life.hpp"
#include "IContext.hpp"
#include "Packet.hpp"
#include "Protocol.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::BasicRandomEnnemiesSystem::operator()(Registry &r, std::shared_ptr<IContext> ctx)
{
    if (_clock.getMiliSeconds() < ENNEMIES_TICK) {
        return;
    }
    if (nbOfBasicEnnemies(r) < MAX_RANDOM_ENNEMIES) {
        createNewEnnemies(r, ctx);
        return;
    }
    _clock.restart();

    auto &animations = r.register_if_not_exist<ecs::component::Animations>();
    auto &positions = r.register_if_not_exist<ecs::component::Position>();
    auto &controllable = r.register_if_not_exist<ecs::component::Controllable>();

    for (auto &&[anim, pos, ctrl] : ecs::custom_zip(animations, positions, controllable)) {
        if (!anim || !pos || !ctrl || anim->_type != ecs::component::Type::Basic) {
            continue;
        }

        if (anim->_object == ecs::component::Object::Weapon && anim->_clock.getMiliSeconds() > 5) {
            pos->_x -= ctrl->_speed;
            anim->_clock.restart();
            continue;
        }

        if (anim->_object != ecs::component::Object::Ennemies) {
            continue;
        }

        if (anim->_x <= 0 && anim->_x != 224) {
            anim->_x = 224;
        }

        if (anim->_x > 0 && anim->_clock.getSeconds() > BASIC_PROJECTILE_SPEED_TICK) {
            anim->_x -= anim->_width;
            anim->_clock.restart();
        }

        if (anim->_clock.getMiliSeconds() > BASIC_ENNEMIES_SPEED_TICK) {
            pos->_x -= ctrl->_speed;
        }

        if (anim->_clock.getSeconds() > SHOOTING_ELAPSED_TIME) {
            shootRandomly(r, *pos, ctx);
        }
    }
}

void ecs::systems::BasicRandomEnnemiesSystem::createNewProjectile(
    Registry &r,
    const ecs::component::Position &ennemiesPos,
    std::shared_ptr<IContext> &ctx
)
{
    Entity newProjectile = r.spawn_entity();
    r._entities.addEntity(newProjectile);
    auto &positions = r.register_if_not_exist<ecs::component::Position>();
    auto &drawables = r.register_if_not_exist<ecs::component::Drawable>();
    auto &controllables = r.register_if_not_exist<ecs::component::Controllable>();
    auto &sprites = r.register_if_not_exist<ecs::component::Sprite>();
    auto &animations = r.register_if_not_exist<ecs::component::Animations>();
    auto &sizes = r.register_if_not_exist<ecs::component::Size>();
    auto &destroyable = r.register_if_not_exist<ecs::component::Destroyable>();
    auto &life = r.register_if_not_exist<ecs::component::Life>();

    life[newProjectile.getId()] = ecs::component::Life{1};
    positions[newProjectile.getId()] = ecs::component::Position{ennemiesPos._x, ennemiesPos._y + CENTERED_SHOOT};
    drawables[newProjectile.getId()] = ecs::component::Drawable{true};
    controllables[newProjectile.getId()] = ecs::component::Controllable{true, BASIC_ENNEMIES_PROJECTILE_SPEED};
    sprites[newProjectile.getId()] = ecs::component::Sprite{ENNEMIES_WEAPON_SPRITE};
    destroyable[newProjectile.getId()] = ecs::component::Destroyable{false};
    animations[newProjectile.getId()] = ecs::component::Animations{
        ecs::Clock(), 20, 18, 0, 0, 0, ecs::component::Object::Weapon, ecs::component::Type::Basic
    };
    sizes[newProjectile.getId()] = ecs::component::Size{3, 3};
    if (ctx && ctx->_network) {
        ctx->_network->broadcast(ecs::Packet(
            protocol::NEW_OBJECT,
            {static_cast<uint8_t>(newProjectile.getId()), static_cast<uint8_t>(protocol::ObjectTypes::BULLET)}
        ));
    }
}

void ecs::systems::BasicRandomEnnemiesSystem::createNewEnnemies(Registry &r, std::shared_ptr<IContext> &ctx)
{
    std::random_device randomPosition;
    std::default_random_engine randomEngine(randomPosition());
    std::uniform_int_distribution<int> uniformDistForY(100, 800);
    std::uniform_int_distribution<int> uniformDistForX(0, 500);
    int randomPosY = uniformDistForY(randomEngine);
    int randomPosX = uniformDistForY(randomEngine);

    Entity newEnnemies = r.spawn_entity();
    r._entities.addEntity(newEnnemies);
    auto &positions = r.register_if_not_exist<ecs::component::Position>();
    auto &drawables = r.register_if_not_exist<ecs::component::Drawable>();
    auto &controllable = r.register_if_not_exist<ecs::component::Controllable>();
    auto &sprites = r.register_if_not_exist<ecs::component::Sprite>();
    auto &animations = r.register_if_not_exist<ecs::component::Animations>();
    auto &sizes = r.register_if_not_exist<ecs::component::Size>();
    auto &destroyable = r.register_if_not_exist<ecs::component::Destroyable>();
    auto &life = r.register_if_not_exist<ecs::component::Life>();

    life[newEnnemies.getId()] = ecs::component::Life{1};
    positions[newEnnemies.getId()] = ecs::component::Position{BASIC_POS_SPAWN_X + randomPosX, randomPosY, false};
    drawables[newEnnemies.getId()] = ecs::component::Drawable{true};
    controllable[newEnnemies.getId()] = ecs::component::Controllable{false, BASIC_ENNEMIES_SPEED};
    sprites[newEnnemies.getId()] = ecs::component::Sprite{BASIC_ENNEMIES_SPRITE};
    animations[newEnnemies.getId()] = ecs::component::Animations{
        ecs::Clock(), 32, 35, 224, 0, 0, ecs::component::Object::Ennemies, ecs::component::Type::Basic
    };
    sizes[newEnnemies.getId()] = ecs::component::Size{2.8, 2.8};
    destroyable[newEnnemies.getId()] = ecs::component::Destroyable{false};
    if (ctx && ctx->_network) {
        ctx->_network->broadcast(ecs::Packet(
            protocol::NEW_OBJECT,
            {static_cast<uint8_t>(newEnnemies.getId()), static_cast<uint8_t>(protocol::ObjectTypes::ENEMY)}
        ));
    }
}

int ecs::systems::BasicRandomEnnemiesSystem::nbOfBasicEnnemies(Registry &r)
{
    int nbOfEnnemies = 0;
    auto &animations = r.register_if_not_exist<ecs::component::Animations>();

    for (std::size_t i = 0; i < animations.size(); ++i) {
        if (animations[i] && animations[i]->_type == ecs::component::Type::Basic) {
            nbOfEnnemies += 1;
        }
    }

    return nbOfEnnemies;
}

void ecs::systems::BasicRandomEnnemiesSystem::shootRandomly(
    Registry &r,
    ecs::component::Position &enemyPos,
    std::shared_ptr<IContext> &ctx
)
{
    std::random_device randomDevice;
    std::default_random_engine randomEngine(randomDevice());
    std::uniform_int_distribution<int> shootChance(0, 100);

    if (shootChance(randomEngine) < 1) {
        createNewProjectile(r, enemyPos, ctx);
    }
}
