/*
** EPITECH PROJECT, 2024
** RType
** File description:
** ParalaxSystem
*/

#ifndef PARALAXSYSTEM_HPP_
#define PARALAXSYSTEM_HPP_

#include "Clock.hpp"

#define BACKGROUND_SPEED 0.01
#define BACKGROUND_TICK 3
#define SCREEN_WIDTH 1920

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
                    if (_clock.getMiliSeconds() < BACKGROUND_TICK) {
                        return;
                    }
                    _clock.restart();
                    auto &paralax = r.get_components<ecs::component::Parallax>();
                    auto &positions = r.get_components<ecs::component::Position>();
                    auto &animation = r.get_components<ecs::component::Animations>();

                    for (auto &&[pos, para, anim] : ecs::custom_zip(positions, paralax, animation)) {
                        if (anim->_object == ecs::component::Object::Background && anim->_clock.getSeconds() > (int)(1 / 60)) {
                            if (pos->_x <= -SCREEN_WIDTH) {
                                pos->_x = SCREEN_WIDTH * para->_multiplicator;
                            }
                            pos->_x -= para->_speed;
                        }
                    }
                }
        
            private:
                Clock _clock;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !PARALAXSYSTEM_HPP_ */
