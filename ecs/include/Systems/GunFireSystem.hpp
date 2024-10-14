#ifndef GUNFIRESYSTEM_HPP_
#define GUNFIRESYSTEM_HPP_

#include "Components/Life.hpp"
#include "IContext.hpp"

#define PROJECTILE_SPEED_ANIMATION 0.1
#define PROJECTILE_SPEED 3
#define PROJECTIL_TICK 2.5

#include <SFML/Window/Keyboard.hpp>

#include "Clock.hpp"
#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class GunFireSystem : public ISystems {
          public:
            bool _wasKeyPressed = false;

            void operator()(Registry &r, std::shared_ptr<IContext> ctx);

          private:
            Clock _clock;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* GUNFIRESYSTEM_HPP_ */
