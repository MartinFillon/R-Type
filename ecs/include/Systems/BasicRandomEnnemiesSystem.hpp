#ifndef BASICRANDOMENNEMIESSYSTEM_HPP_
#define BASICRANDOMENNEMIESSYSTEM_HPP_

#include "ComponentFactory.hpp"
#include "Components/Position.hpp"
#include "IContext.hpp"

#include "Clock.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class BasicRandomEnnemiesSystem : public ISystems {
          public:
            BasicRandomEnnemiesSystem(const nlohmann::json &j);

            void createNewProjectile(
                std::shared_ptr<Registry> &r,
                const ecs::component::Position &ennemiesPos,
                std::shared_ptr<IContext> &ctx
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
                std::shared_ptr<IContext> &ctx
            );
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

          private:
            Clock _clock;
            Clock _shootingClock;
            int _maxNbOfEnnemies;
            int _ennemiesTick;
            int _valueSpawnEnnemies;
            int _basicPosSpawnX;
            int _maxSpawnX;
            int _shootingElapsedTime;
            int _basicEnnemiesAnimationSpeed;
            int _basicEnnemiesSpeed;
            double _basicEnnemiesProjectileSpeed;
            int _basicProjectileSpeedTick;
            int _centeredShoot;
            int _basicEnnemiesSpeedTick;
            std::string _enemmiesConfigFile;
            std::string _projectileConfigFile;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !BASICRANDOMENNEMIESSYSTEM_HPP_ */
