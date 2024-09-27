/*
** EPITECH PROJECT, 2024
** RType
** File description:
** PlayerMouvementSystem
*/

#ifndef PLAYERMOUVEMENTSYSTEM_HPP_
#define PLAYERMOUVEMENTSYSTEM_HPP_

#include <SFML/Window/Keyboard.hpp>

#include "Components/Controllable.hpp"
#include "Components/Animations.hpp"
#include "Components/Position.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"
//35
namespace ecs {
    namespace systems {
        class PlayerMouvementSystem : public ISystems {
          public:
            void operator()(Registry &r) {
                auto &positions = r.get_components<ecs::component::Position>();
                auto &controllable = r.get_components<ecs::component::Controllable>();
                auto &animations = r.get_components<ecs::component::Animations>();

                for (std::size_t i = 0; i < positions.size(); ++i) {
                    if (positions[i] && controllable[i]) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            positions[i]->_y -= controllable[i]->_speed;
                            if (animations[i]->_clock.getElapsedTime().asSeconds() > 0.5 && animations[i]->_x < 135) {
                                animations[i]->_x += 35;
                                animations[i]->_clock.restart();
                            }
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            positions[i]->_y += controllable[i]->_speed;
                            if (animations[i]->_clock.getElapsedTime().asSeconds() > 0.5 && animations[i]->_x > 0) {
                                animations[i]->_x -= 35;
                                animations[i]->_clock.restart();
                            }
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            positions[i]->_x -= controllable[i]->_speed;
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            positions[i]->_x += controllable[i]->_speed;
                        }
                    }
                }
            };
        };
    }; // namespace systems
}; // namespace ecs

#endif /* PLAYERMOUVEMENTSYSTEM_HPP_ */
