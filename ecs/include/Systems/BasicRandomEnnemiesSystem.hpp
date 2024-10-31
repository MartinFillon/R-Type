/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** BasicRandomEnnemiesSystem
*/

#ifndef BASICRANDOMENNEMIESSYSTEM_HPP_
#define BASICRANDOMENNEMIESSYSTEM_HPP_

#define BASIC_RANDOM_ENNEMIES_SYSTEM "Basic random ennemies system"

#include "ComponentFactory.hpp"
#include "Components/Position.hpp"
#include "Defs.hpp"
#include "IContext.hpp"

#include "Clock.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class BasicRandomEnnemiesSystem : public ISystems {
          public:
            BasicRandomEnnemiesSystem(const nlohmann::json &j);

            std::string getName() const override {
                return BASIC_RANDOM_ENNEMIES_SYSTEM;
            }

            void createNewProjectile(
                std::shared_ptr<Registry> &r,
                const ecs::component::Position &ennemiesPos,
                std::shared_ptr<IContext> &ctx,
                ComponentFactory &factory
            );
            void createNewEnnemies(
                std::shared_ptr<Registry> &r,
                std::shared_ptr<IContext> &ctx,
                ComponentFactory &factory
            );
            int nbOfBasicEnnemies(std::shared_ptr<Registry> &r);
            void shootRandomly(
                std::shared_ptr<Registry> &r,
                ecs::component::Position &enemyPos,
                std::shared_ptr<IContext> &ctx,
                ComponentFactory &factory
            );
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

          private:
            Clock _clock;
            Clock _shootingClock;
            int _maxNbOfEnnemies = MAX_RANDOM_ENNEMIES;
            int _ennemiesTick = ENNEMIES_TICK;
            int _valueSpawnEnnemies = VALUE_SPAWN_ENNEMIES;
            int _basicPosSpawnX = BASIC_POS_SPAWN_X;
            int _maxSpawnX = MAX_SPAWN_X;
            double _shootingElapsedTime = SHOOTING_ELAPSED_TIME;
            double _basicEnnemiesAnimationSpeed = BASIC_ENNEMIES_ANIMATON_SPEED;
            double _basicEnnemiesSpeed = BASIC_ENNEMIES_SPEED;
            double _basicEnnemiesProjectileSpeed = BASIC_ENNEMIES_PROJECTILE_SPEED;
            double _basicProjectileSpeedTick = BASIC_PROJECTILE_SPEED_TICK;
            int _centeredShoot = CENTERED_SHOOT;
            int _basicEnnemiesSpeedTick = BASIC_ENNEMIES_SPEED_TICK;
            std::string _enemmiesConfigFile = CONFIG_ENNEMIES;
            std::string _projectileConfigFile = CONFIG_PROJECTILE;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !BASICRANDOMENNEMIESSYSTEM_HPP_ */
