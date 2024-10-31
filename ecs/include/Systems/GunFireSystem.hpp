#ifndef GUNFIRESYSTEM_HPP_
#define GUNFIRESYSTEM_HPP_

#include "ComponentFactory.hpp"
#include "IContext.hpp"

#define PROJECTILE_SPEED_ANIMATION 0.1
#define PROJECTILE_SPEED 3
#define PROJECTIL_TICK 2.5
#define GUN_FIRE_SYSTEM_NAME "Gun Fire System"

#include "Clock.hpp"

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class GunFireSystem : public ISystems {
          public:
            GunFireSystem() = default;
            bool _wasKeyPressed = false;

            std::string getName() const override {
                return GUN_FIRE_SYSTEM_NAME;
            }

            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

          private:
            Clock _clock;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* GUNFIRESYSTEM_HPP_ */
