/*
** EPITECH PROJECT, 2024
** RType
** File description:
** PlayerMouvementSystem
*/

#ifndef PLAYERMOUVEMENTSYSTEM_HPP_
#define PLAYERMOUVEMENTSYSTEM_HPP_

#include "Clock.hpp"
#define PLAYER_MOVE_ANIMATION 0.2
#define PLAYER_MOUVEMENT_TICK 3

#include <SFML/Window/Keyboard.hpp>

#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Position.hpp"

#include "ISystems.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

namespace ecs {
    namespace systems {
        class PlayerMouvementSystem : public ISystems {
            public:
                void operator()(Registry &r)
                {
                    if (_clock.getMiliSeconds() < PLAYER_MOUVEMENT_TICK) {
                        return;
                    }
                    _clock.restart();
                    auto &positions = r.get_components<ecs::component::Position>();
                    auto &controllables = r.get_components<ecs::component::Controllable>();
                    auto &animations = r.get_components<ecs::component::Animations>();
                    auto &drawable = r.register_component<ecs::component::Drawable>();
                    auto &sprite = r.register_component<ecs::component::Sprite>();
                    auto &parallax = r.register_component<ecs::component::Parallax>();
                    auto &size = r.register_component<ecs::component::Size>();

                    for (auto &&[position, controllable, animation] :
                         ecs::custom_zip(positions, controllables, animations)) {
                        if (animation->_object == ecs::component::Object::Player) {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                                position->_y -= controllable->_speed;
                                if (animation->_clock.getSeconds() > PLAYER_MOVE_ANIMATION &&
                                    animation->_x < 135) {
                                    animation->_x += 35;
                                    animation->_clock.restart();
                                }
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                                position->_y += controllable->_speed;
                                if (animation->_clock.getSeconds() > PLAYER_MOVE_ANIMATION &&
                                    animation->_x > 0) {
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

            private:
                Clock _clock;
        };
    }; // namespace systems
} // namespace ecs

#endif /* PLAYERMOUVEMENTSYSTEM_HPP_ */
