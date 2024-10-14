#ifndef BASICRANDOMENNEMIESSYSTEM_HPP_
#define BASICRANDOMENNEMIESSYSTEM_HPP_

#include "IContext.hpp"
#define ENNEMIES_TICK 2

#define MAX_RANDOM_ENNEMIES 4
#define VALUE_SPAWN_ENNEMIES 2

#define BASIC_POS_SPAWN_X 1944
#define MAX_SPAWN_X 2500

#define SHOOTING_ELAPSED_TIME 0.2

#define BASIC_ENNEMIES_ANIMATON_SPEED 0.24
#define BASIC_ENNEMIES_SPEED 1.8
#define BASIC_ENNEMIES_PROJECTILE_SPEED 10
#define BASIC_PROJECTILE_SPEED_TICK 0.3
#define CENTERED_SHOOT 15
#define BASIC_ENNEMIES_SPEED_TICK 8

#include "Clock.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class BasicRandomEnnemiesSystem : public ISystems {
          public:
            void createNewProjectile(
                Registry &r,
                const ecs::component::Position &ennemiesPos,
                std::shared_ptr<IContext> &ctx
            );
            void createNewEnnemies(Registry &r, std::shared_ptr<IContext> &ctx);
            int nbOfBasicEnnemies(Registry &r);
            void shootRandomly(Registry &r, ecs::component::Position &enemyPos, std::shared_ptr<IContext> &ctx);
            void operator()(Registry &, std::shared_ptr<IContext> ctx) override;

          private:
            Clock _clock;
            Clock _shootingClock;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !BASICRANDOMENNEMIESSYSTEM_HPP_ */
