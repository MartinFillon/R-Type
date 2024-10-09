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
#define BOSS_SPAWN_TIME 600
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
#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Life.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

namespace ecs {
    namespace systems {
        class BossSystems : public ISystems {
          public:

            void operator()(Registry &r);

            void createNewProjectile(Registry &r, const ecs::component::Position &bossPos);
            void createFirstBoss(Registry &r);
            bool isABoss(Registry &r);
            void moveProjectileTowardsPlayer(
                Registry &r,
                ecs::component::Position &projectilePos,
                const std::size_t &idx);

          private:
            ecs::Clock _bossClock;
            ecs::Clock _shootingClock;
            ecs::Clock _projectileClock;
            std::size_t times = 0;
            std::array<std::function<void(Registry &r)>, 1> _bosses{
                {[this](Registry &r) { createFirstBoss(r); }},
            };
        };
    } // namespace systems
} // namespace ecs

#endif /* !BOSSSYSTEMS_HPP_ */
