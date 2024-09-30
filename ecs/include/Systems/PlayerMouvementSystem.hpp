/*
** EPITECH PROJECT, 2024
** RType
** File description:
** PlayerMouvementSystem
*/

#ifndef PLAYERMOUVEMENTSYSTEM_HPP_
#define PLAYERMOUVEMENTSYSTEM_HPP_

#define PLAYER_MOVE_ANIMATION 0.2

#include <SFML/Window/Keyboard.hpp>

#include "GunFireSystem.hpp"

#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"

#include "ZipperIterator.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class PlayerMouvementSystem : public ISystems {
        public:
            void operator()(Registry &r)
            {
                auto &positions = r.get_components<ecs::component::Position>();
                auto &controllables = r.get_components<ecs::component::Controllable>();
                auto &animations = r.get_components<ecs::component::Animations>();

                for (auto &&[position, controllable, animation] : ecs::custom_zip(positions, controllables, animations)) {
                    if (animation->_object == ecs::component::Object::Player) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            position->_y -= controllable->_speed;
                            if (animation->_clock.getElapsedTime().asSeconds() > PLAYER_MOVE_ANIMATION && animation->_x < 135) {
                                animation->_x += 35;
                                animation->_clock.restart();
                            }
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            position->_y += controllable->_speed;
                            if (animation->_clock.getElapsedTime().asSeconds() > PLAYER_MOVE_ANIMATION && animation->_x > 0) {
                                animation->_x -= 35;
                                animation->_clock.restart();
                            }
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            position->_x -= controllable->_speed;
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            position->_x += controllable->_speed;
                        }
                    }
                }
            }
        };
    }; // namespace systems
} // namespace ecs

#endif /* PLAYERMOUVEMENTSYSTEM_HPP_ */
