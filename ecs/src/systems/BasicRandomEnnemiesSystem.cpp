/*
** EPITECH PROJECT, 2024
** ennemy moves system file
** File description:
** BasicRandomEnnemiesSystem
*/

#include "Systems/BasicRandomEnnemiesSystem.hpp"
#include <Components/Attributes.hpp>
#include <iostream>
#include <memory>
#include <random>
#include "ComponentFactory.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Life.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "IContext.hpp"
#include "Protocol.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::BasicRandomEnnemiesSystem::operator()(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<IContext> ctx,
    ComponentFactory &factory
)
{
    if (_clock.getMiliSeconds() < ENNEMIES_TICK) {
        return;
    }
    if (nbOfBasicEnnemies(r) < MAX_RANDOM_ENNEMIES) {
        createNewEnnemies(r, ctx, factory);
        return;
    }
    _clock.restart();

    auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();
    auto &animations = r->register_if_not_exist<ecs::component::Animations>();
    auto &positions = r->register_if_not_exist<ecs::component::Position>();
    auto &controllable = r->register_if_not_exist<ecs::component::Controllable>();

    for (auto &&[atr, anim, pos, ctrl] : ecs::custom_zip(attributes, animations, positions, controllable)) {
        if (!atr || !anim || !pos || !ctrl || atr->_ennemy_type != ecs::component::Attributes::EnnemyType::Basic) {
            continue;
        }

        if (atr->_entity_type == ecs::component::Attributes::EntityType::Weapon && anim->_clock.getMiliSeconds() > 5) {
            pos->_x -= ctrl->_speed;
            anim->_clock.restart();
            continue;
        }

        if (atr->_entity_type != ecs::component::Attributes::EntityType::Ennemy) {
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
            shootRandomly(r, *pos, ctx, factory);
        }
    }
}

void ecs::systems::BasicRandomEnnemiesSystem::createNewProjectile(
    std::shared_ptr<Registry> &r,
    const ecs::component::Position &ennemiesPos,
    std::shared_ptr<IContext> &ctx,
    ComponentFactory &factory
)
{
    Entity newProjectile = factory.createEntity(r, CONFIG_PROJECTILE);

    auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();
    auto &positions = r->register_if_not_exist<ecs::component::Position>();

    positions[newProjectile.getId()] = ecs::component::Position{ennemiesPos._x, ennemiesPos._y + CENTERED_SHOOT};
    if (ctx) {
        ctx->createProjectile(newProjectile.getId(), rtype::protocol::BULLET);
    }
}

void ecs::systems::BasicRandomEnnemiesSystem::createNewEnnemies(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<IContext> &ctx,
    ComponentFactory &factory
)
{
    std::random_device randomPosition;
    std::default_random_engine randomEngine(randomPosition());
    std::uniform_int_distribution<int> uniformDistForY(100, 800);
    std::uniform_int_distribution<int> uniformDistForX(0, 500);
    int randomPosY = uniformDistForY(randomEngine);
    int randomPosX = uniformDistForY(randomEngine);

    Entity newEnnemies = factory.createEntity(r, CONFIG_ENNEMIES);
    auto &positions = r->register_if_not_exist<ecs::component::Position>();
    positions[newEnnemies.getId()] = ecs::component::Position{BASIC_POS_SPAWN_X + randomPosX, randomPosY, false};

    if (ctx) {
        ctx->createEnemy(newEnnemies.getId());
    }
}

int ecs::systems::BasicRandomEnnemiesSystem::nbOfBasicEnnemies(std::shared_ptr<Registry> &r)
{
    int nbOfEnnemies = 0;
    auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();

    for (std::size_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i] && attributes[i]->_entity_type == ecs::component::Attributes::EntityType::Ennemy &&
            attributes[i]->_ennemy_type == ecs::component::Attributes::EnnemyType::Basic) {
            nbOfEnnemies += 1;
        }
    }

    return nbOfEnnemies;
}

void ecs::systems::BasicRandomEnnemiesSystem::shootRandomly(
    std::shared_ptr<Registry> &r,
    ecs::component::Position &enemyPos,
    std::shared_ptr<IContext> &ctx,
    ComponentFactory &factory
)
{
    std::random_device randomDevice;
    std::default_random_engine randomEngine(randomDevice());
    std::uniform_int_distribution<int> shootChance(0, 100);

    if (shootChance(randomEngine) < 1) {
        createNewProjectile(r, enemyPos, ctx, factory);
    }
}
