#ifndef GUNFIRESYSTEM_HPP_
#define GUNFIRESYSTEM_HPP_

#include "ComponentFactory.hpp"
#include "IContext.hpp"

#define PROJECTILE_SPEED_ANIMATION 0.1
#define PROJECTILE_SPEED 3
#define PROJECTIL_TICK 2.5

#include <SFML/Window/Keyboard.hpp>

#include "Clock.hpp"

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class GunFireSystem : public ISystems {
          public:
            GunFireSystem() = default;
            bool _wasKeyPressed = false;

            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

          private:
            Clock _clock;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* GUNFIRESYSTEM_HPP_ */
