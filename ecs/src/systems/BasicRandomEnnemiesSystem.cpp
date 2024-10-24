/*
** EPITECH PROJECT, 2024
** ennemy moves system file
** File description:
** BasicRandomEnnemiesSystem
*/

#include "Systems/BasicRandomEnnemiesSystem.hpp"
#include <fstream>
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

        auto &animations = r->register_if_not_exist<ecs::component::Animations>();
        auto &positions = r->register_if_not_exist<ecs::component::Position>();
        auto &controllable = r->register_if_not_exist<ecs::component::Controllable>();

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

            if (anim->_x > 0 && anim->_clock.getSeconds() > _basicEnnemiesAnimationSpeed) {
                anim->_x -= anim->_width;
                anim->_clock.restart();
            }

            if (anim->_clock.getMiliSeconds() > _basicEnnemiesSpeedTick) {
                pos->_x -= ctrl->_speed;
            }

            if (anim->_clock.getSeconds() > _basicEnnemiesSpeed) {
                shootRandomly(r, *pos, ctx);
            }
        }
    }

    void BasicRandomEnnemiesSystem::createNewProjectile(
        std::shared_ptr<Registry> &r,
        const ecs::component::Position &ennemiesPos,
        std::shared_ptr<IContext> &ctx
    )
    {
        Entity newProjectile = r->spawn_entity();
        r->_entities.addEntity(newProjectile);
        auto &positions = r->register_if_not_exist<ecs::component::Position>();
        auto &drawables = r->register_if_not_exist<ecs::component::Drawable>();
        auto &controllables = r->register_if_not_exist<ecs::component::Controllable>();
        auto &sprites = r->register_if_not_exist<ecs::component::Sprite>();
        auto &animations = r->register_if_not_exist<ecs::component::Animations>();
        auto &sizes = r->register_if_not_exist<ecs::component::Size>();
        auto &destroyable = r->register_if_not_exist<ecs::component::Destroyable>();
        auto &life = r->register_if_not_exist<ecs::component::Life>();

        life[newProjectile.getId()] = ecs::component::Life{1};
        positions[newProjectile.getId()] = ecs::component::Position{ennemiesPos._x, ennemiesPos._y + _centeredShoot};
        drawables[newProjectile.getId()] = ecs::component::Drawable{true};
        controllables[newProjectile.getId()] = ecs::component::Controllable{true, _basicEnnemiesProjectileSpeed};
        sprites[newProjectile.getId()] = ecs::component::Sprite{ENNEMIES_WEAPON_SPRITE};
        destroyable[newProjectile.getId()] = ecs::component::Destroyable{false};
        animations[newProjectile.getId()] = ecs::component::Animations{
            ecs::Clock(), 20, 18, 0, 0, 0, ecs::component::Object::Weapon, ecs::component::Type::Basic
        };
        sizes[newProjectile.getId()] = ecs::component::Size{3, 3};
        if (ctx) {
            ctx->createProjectile(newProjectile.getId(), rtype::protocol::BULLET);
        }
    }

    void BasicRandomEnnemiesSystem::createNewEnnemies(
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

        Entity newEnnemies = factory.createEntity(r, _enemmiesConfigFile);
        auto &positions = r->register_if_not_exist<ecs::component::Position>();
        positions[newEnnemies.getId()] = ecs::component::Position{_basicPosSpawnX + randomPosX, randomPosY, false};

        if (ctx) {
            ctx->createEnemy(newEnnemies.getId());
        }
    }

    int BasicRandomEnnemiesSystem::nbOfBasicEnnemies(std::shared_ptr<Registry> &r)
    {
        int nbOfEnnemies = 0;
        auto &animations = r->register_if_not_exist<ecs::component::Animations>();

        for (std::size_t i = 0; i < animations.size(); ++i) {
            if (animations[i] && animations[i]->_type == ecs::component::Type::Basic) {
                nbOfEnnemies += 1;
            }
        }

        return nbOfEnnemies;
    }

    void BasicRandomEnnemiesSystem::shootRandomly(
        std::shared_ptr<Registry> &r,
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

} // namespace ecs::systems
