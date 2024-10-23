/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BossSystems
*/

#ifndef BOSSSYSTEMS_HPP_
#define BOSSSYSTEMS_HPP_

#include "Components/Position.hpp"
#define BOSS_LIFE(x) 100 * x
#define BOSS_SPEED 5
#define BOSS_SPAWN_TIME 60
#define BOSS_PROJECTILE_SPEED 5
#define MOVING_PROJECTILE_SPEED 0.01
#define BOSS_PROJECTILE_SPAWN_TIME 3
#define BOSS_SHOOTING_ELAPSED_TIME 0.5

#define PROJECTILE_CLOSE 200
#define PROJECTILE_PADDING 100

#include <array>
#include <cmath>
#include <functional>

#include "Clock.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class BossSystems : public ISystems {
          public:
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

            void createNewProjectile(
                std::shared_ptr<Registry> &r,
                const ecs::component::Position &bossPos,
                std::shared_ptr<IContext> ctx
            );
            void createFirstBoss(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx);
            bool isABoss(std::shared_ptr<Registry> &r);
            void moveProjectileTowardsPlayer(
                std::shared_ptr<Registry> &r,
                ecs::component::Position &projectilePos,
                const std::size_t &idx,
                std::shared_ptr<IContext> ctx
            );

          private:
            ecs::Clock _bossClock;
            ecs::Clock _shootingClock;
            ecs::Clock _projectileClock;
            std::size_t times = 0;
            std::array<std::function<void(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx)>, 1> _bosses{
                {[this](std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx) { createFirstBoss(r, ctx); }},
            };
        };
    } // namespace systems
} // namespace ecs

#endif /* !BOSSSYSTEMS_HPP_ */
