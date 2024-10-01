/*
** EPITECH PROJECT, 2024
** RType
** File description:
** ParalaxSystem
*/

#ifndef PARALAXSYSTEM_HPP_
#define PARALAXSYSTEM_HPP_

#define BACKGROUND_SPEED 0.01

#include <SFML/Config.hpp>
#include "Components/Animations.hpp"
#include "Components/Parallax.hpp"
#include "Components/Position.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

namespace ecs {
    namespace systems {
        class ParalaxSystem : public ISystems {
          public:
            void operator()(Registry &r)
            {
                auto &paralax = r.get_components<ecs::component::Parallax>();
                auto &positions = r.get_components<ecs::component::Position>();
                auto &animation = r.get_components<ecs::component::Animations>();

                for (auto &&[pos, para, anim] : ecs::custom_zip(positions, paralax, animation)) {
                    if (anim->_object == ecs::component::Object::Background) {
                        if (anim->_clock.getElapsedTime().asMicroseconds() > 0.1) {
                            if (pos->_x <= -1920) {
                                pos->_x = 1920 * para->_multiplicator;
                            }
                            anim->_clock.restart();
                            pos->_x -= para->_speed;
                        }
                    }
                }
            }
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !PARALAXSYSTEM_HPP_ */
