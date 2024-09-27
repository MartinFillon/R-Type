/*
** EPITECH PROJECT, 2024
** RType
** File description:
** GunFireSystem
*/

#ifndef GUNFIRESYSTEM_HPP_
#define GUNFIRESYSTEM_HPP_

#include <SFML/Window/Keyboard.hpp>
#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Position.hpp"
#include "Components/Drawable.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class GunFireSystem : public ISystems {
          public:
            void operator()(Registry &r)
            {
                auto &positions = r.get_components<ecs::component::Position>();
                auto &controllable = r.get_components<ecs::component::Controllable>();
                auto &animations = r.get_components<ecs::component::Animations>();
                auto &drawable = r.get_components<ecs::component::Drawable>();
                ecs::component::Position playerPos;

                for (std::size_t i = 0; i < positions.size(); ++i) {
                    if (animations[i] && animations[i]->_object == ecs::component::Object::Player) {
                        playerPos._x = positions[i]->_x + 100;
                        playerPos._y = positions[i]->_y + 10;
                    }
                    if (positions[i] && controllable[i] && animations[i]->_object == ecs::component::Object::Weapon) {
                        if (!drawable[i]->_drawable) {
                            positions[i] = playerPos;
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) || drawable[i]->_drawable) {
                            if (animations[i]->_x < 30) {
                                positions[i] = playerPos;
                            }
                            if (animations[i]->_clock.getElapsedTime().asSeconds() > 0.5 && animations[i]->_x < 30) {
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
        };
    }; // namespace systems
}; // namespace ecs

#endif /* GUNFIRESYSTEM_HPP_ */
