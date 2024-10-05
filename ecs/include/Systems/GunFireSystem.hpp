#ifndef GUNFIRESYSTEM_HPP_
#define GUNFIRESYSTEM_HPP_

#define PROJECTILE_SPEED_ANIMATION 0.1
#define PROJECTILE_SPEED 3

#include <SFML/Window/Keyboard.hpp>

#include "Clock.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
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
            bool wasKeyPressed = false;

            void createNewProjectile(Registry &r, const ecs::component::Position &playerPos)
            {
                Entity newProjectile = r.spawn_entity();
                r._entities.addEntity(newProjectile);
                auto &positions = r.get_components<ecs::component::Position>();
                auto &drawables = r.get_components<ecs::component::Drawable>();
                auto &controllables = r.get_components<ecs::component::Controllable>();
                auto &sprites = r.get_components<ecs::component::Sprite>();
                auto &animations = r.get_components<ecs::component::Animations>();
                auto &sizes = r.get_components<ecs::component::Size>();
                auto &destroyable = r.get_components<ecs::component::Destroyable>();

                positions[newProjectile.getId()] = ecs::component::Position{playerPos._x, playerPos._y};
                drawables[newProjectile.getId()] = ecs::component::Drawable{true};
                controllables[newProjectile.getId()] = ecs::component::Controllable{true, PROJECTILE_SPEED};
                sprites[newProjectile.getId()] = ecs::component::Sprite{WEAPON_SPRITE};
                destroyable[newProjectile.getId()] = ecs::component::Destroyable{false};
                animations[newProjectile.getId()] =
                    ecs::component::Animations{ecs::Clock(), 18, 12, 0, 0, 0, ecs::component::Object::Weapon, ecs::component::EnnemiesObject::None};
                sizes[newProjectile.getId()] = ecs::component::Size{3, 3};
            }

            void operator()(Registry &r)
            {
                auto &positions = r.get_components<ecs::component::Position>();
                auto &controllable = r.get_components<ecs::component::Controllable>();
                auto &animations = r.get_components<ecs::component::Animations>();
                auto &drawable = r.get_components<ecs::component::Drawable>();
                auto &destroyable = r.get_components<ecs::component::Destroyable>();

                ecs::component::Position playerPos = {0, 0};

                for (std::size_t i = 0; i < positions.size(); ++i) {
                    if (animations[i] && animations[i]->_object == ecs::component::Object::Player) {
                        playerPos._x = positions[i]->_x + 100;
                        playerPos._y = positions[i]->_y + 10;
                        break;
                    }
                }

                if (playerPos._x == 0.0 && playerPos._y == 0.0) {
                    return;
                }

                bool isKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::X);

                if (isKeyPressed && !wasKeyPressed) {
                    createNewProjectile(r, playerPos);
                }

                wasKeyPressed = isKeyPressed;

                for (std::size_t i = 0; i < positions.size(); ++i) {
                    if (drawable[i] && !drawable[i]->_drawable) {
                        continue;
                    }

                    if (positions[i] && controllable[i] && animations[i] && animations[i]->_object == ecs::component::Object::Weapon) {
                        if (animations[i]->_x < 30) {
                            positions[i] = playerPos;
                        }
                        if (animations[i]->_clock.getSeconds() > PROJECTILE_SPEED_ANIMATION &&
                            animations[i]->_x < 30) {
                            animations[i]->_x += 18;
                            animations[i]->_clock.restart();
                        }
                        if (animations[i]->_x > 30 && drawable[i]->_drawable) {
                            positions[i]->_x += controllable[i]->_speed;
                        }
                        drawable[i]->_drawable = true;
                    }
                }
            }
        };
    }; // namespace systems
}; // namespace ecs

#endif /* GUNFIRESYSTEM_HPP_ */
