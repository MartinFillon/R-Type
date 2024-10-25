/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BossSystems
*/

#ifndef BOSSSYSTEMS_HPP_
#define BOSSSYSTEMS_HPP_

#define BOSS_LIFE(x) 100 * x
#define BOSS_SPEED 5
#define BOSS_SPAWN_TIME 60
#define BOSS_PROJECTILE_SPEED 5
#define MOVING_PROJECTILE_SPEED 0.01
#define BOSS_PROJECTILE_SPAWN_TIME 3
#define BOSS_SHOOTING_ELAPSED_TIME 0.5

#define PROJECTILE_CLOSE 200
#define PROJECTILE_PADDING 100

/**

 */

#include <array>
#include <cmath>
#include <functional>

#include "Clock.hpp"
#include "Components/Position.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class BossSystems : public ISystems {
          public:
            BossSystems(const nlohmann::json &config);

            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

            void createNewProjectile(
                std::shared_ptr<Registry> &r,
                const ecs::component::Position &bossPos,
                std::shared_ptr<IContext> ctx,
                ComponentFactory &factory
            );
            void createFirstBoss(
                std::shared_ptr<Registry> &r,
                std::shared_ptr<IContext> ctx,
                ComponentFactory &factory
            );
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
            std::array<
                std::function<
                    void(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)>,
                1>
                _bosses{
                    {[this](std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory) {
                        createFirstBoss(r, ctx, factory);
                    }},
                };
            int _bossLife;
            int _bossSpeed;
            int _bossProjectileSpeed;
            int _movingProjectileSpeed;
            int _bossProjectileSpawnTime;
            int _bossShootingElapsedTime;
            int _projectileClose;
            int _projectilePadding;
            int _bossSpawnTime;
            std::string _bossConfig;
            std::string _projectileConfig;
        };
    } // namespace systems
} // namespace ecs

#endif /* !BOSSSYSTEMS_HPP_ */
