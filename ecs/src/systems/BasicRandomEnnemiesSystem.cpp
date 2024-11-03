/*
** EPITECH PROJECT, 2024
** ennemy moves system file
** File description:
** BasicRandomEnnemiesSystem
*/

#include "Systems/BasicRandomEnnemiesSystem.hpp"
#include <Components/Attributes.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <spdlog/spdlog.h>
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
#include <nlohmann/json-schema.hpp>

namespace ecs::systems {

    BasicRandomEnnemiesSystem::BasicRandomEnnemiesSystem(const nlohmann::json &config)
    {
        std::ifstream schemaFile("schema/BasicRandomEnnemiesSystem.json");

        const nlohmann::json schema = nlohmann::json::parse(schemaFile);

        nlohmann::json_schema::json_validator validator(schema);

        validator.set_root_schema(schema);
        validator.validate(config);

        _ennemiesTick = config["ennemies_tick"];
        _maxNbOfEnnemies = config["max_random_ennemies"];
        _valueSpawnEnnemies = config["value_spawn_ennemies"];
        _basicPosSpawnX = config["basic_pos_spawn_x"];
        _maxSpawnX = config["max_spawn_x"];
        _shootingElapsedTime = config["shooting_elapsed_time"];
        _basicEnnemiesAnimationSpeed = config["basic_ennemies_animation_speed"];
        _basicEnnemiesSpeed = config["basic_ennemies_speed"];
        _basicEnnemiesProjectileSpeed = config["basic_ennemies_projectile_speed"];
        _basicProjectileSpeedTick = config["basic_projectile_speed_tick"];
        _centeredShoot = config["centered_shoot"];
        _basicEnnemiesSpeedTick = config["basic_ennemies_speed_tick"];
        _enemmiesConfigFile = config["ennemies_config_file"];
        _projectileConfigFile = config["projectile_config_file"];
    }

    void BasicRandomEnnemiesSystem::operator()(
        std::shared_ptr<Registry> &r,
        std::shared_ptr<IContext> ctx,
        ComponentFactory &factory
    )
    {
        if (_clock.getMiliSeconds() < _ennemiesTick) {
            return;
        }
        if (nbOfBasicEnnemies(r) < _maxNbOfEnnemies) {
            createNewEnnemies(r, ctx, factory);
            return;
        }
        _clock.restart();

        auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();
        auto &animations = r->register_if_not_exist<ecs::component::Animations>();
        auto &positions = r->register_if_not_exist<ecs::component::Position>();
        auto &controllable = r->register_if_not_exist<ecs::component::Controllable>();

        for (auto &&[atr, anim, pos, ctrl] : ecs::custom_zip(attributes, animations, positions, controllable)) {
            if (!atr || !anim || !pos || !ctrl ||
                atr->_secondary_type != ecs::component::Attributes::SecondaryType::Basic) {
                continue;
            }

            if (atr->_entity_type == ecs::component::Attributes::EntityType::Weapon &&
                anim->_clock.getMiliSeconds() > _shootingElapsedTime) {
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

            if (anim->_x > 0 && anim->_clock.getSeconds() > _basicEnnemiesAnimationSpeed) {
                anim->_x -= anim->_width;
                anim->_clock.restart();
            }

            if (anim->_clock.getMiliSeconds() > _basicEnnemiesSpeedTick) {
                pos->_x -= ctrl->_speed;
            }

            if (anim->_clock.getSeconds() > _shootingElapsedTime) {
                shootRandomly(r, *pos, ctx, factory);
            }
        }
    }

    void BasicRandomEnnemiesSystem::createNewProjectile(
        std::shared_ptr<Registry> &r,
        const ecs::component::Position &ennemiesPos,
        std::shared_ptr<IContext> &ctx,
        ComponentFactory &factory
    )
    {
        Entity newProjectile = factory.createEntity(r, CONFIG_PROJECTILE);

        auto &positions = r->register_if_not_exist<ecs::component::Position>();

        positions[newProjectile.getId()] = ecs::component::Position{ennemiesPos._x, ennemiesPos._y + _centeredShoot};

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

        try {
            Entity newEnnemies = factory.createEntity(r, _enemmiesConfigFile);
            auto &positions = r->register_if_not_exist<ecs::component::Position>();
            positions[newEnnemies.getId()] = ecs::component::Position{_basicPosSpawnX + randomPosX, randomPosY, false};

            if (ctx) {
                ctx->createEnemy(newEnnemies.getId());
            }
        } catch (const ecs::ComponentFactory::ComponentFactoryException &error) {
            std::cerr << error.what() << std::endl;
        }
    }

    int BasicRandomEnnemiesSystem::nbOfBasicEnnemies(std::shared_ptr<Registry> &r)
    {
        int nbOfEnnemies = 0;
        auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();

        for (auto &&[attribute] : ecs::custom_zip(attributes)) {
            if (attribute && attribute->_entity_type == ecs::component::Attributes::EntityType::Ennemy &&
                attribute->_secondary_type == ecs::component::Attributes::SecondaryType::Basic) {
                nbOfEnnemies += 1;
            }
        }

        return nbOfEnnemies;
    }

    void BasicRandomEnnemiesSystem::shootRandomly(
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

} // namespace ecs::systems
