/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BossSystems
*/

#ifndef BOSSSYSTEMS_HPP_
#define BOSSSYSTEMS_HPP_

#define BOSS_SYSTEM "Boss systems"

#include <array>
#include <cmath>
#include <functional>

#include "Clock.hpp"
#include "Components/Position.hpp"
#include "Defs.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class BossSystems : public ISystems {
          public:
            BossSystems() = default;
            BossSystems(const nlohmann::json &config);

            std::string getName() const override {
                return BOSS_SYSTEM;
            }

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
            int _bossLife = 100;
            int _bossSpeed = BOSS_SPEED;
            int _bossProjectileSpeed = BOSS_PROJECTILE_SPEED;
            double _movingProjectileSpeed = MOVING_PROJECTILE_SPEED;
            int _bossProjectileSpawnTime = BOSS_PROJECTILE_SPAWN_TIME;
            double _bossShootingElapsedTime = BOSS_SHOOTING_ELAPSED_TIME;
            int _projectileClose = PROJECTILE_CLOSE;
            int _projectilePadding = PROJECTILE_PADDING;
            int _bossSpawnTime = BOSS_SPAWN_TIME;
            int _bossMaxX = 1920;
            std::string _bossConfig = CONFIG_BOSS;
            std::string _projectileConfig = CONFIG_PROJECTILE;
        };
    } // namespace systems
} // namespace ecs

#endif /* !BOSSSYSTEMS_HPP_ */
