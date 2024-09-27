/*
** EPITECH PROJECT, 2024
** RType
** File description:
** ParalaxSystem
*/

#ifndef PARALAXSYSTEM_HPP_
    #define PARALAXSYSTEM_HPP_

#include <SFML/Config.hpp>
#include "Components/Animations.hpp"
#include "Components/Position.hpp"
#include "Components/Parallax.hpp"
#include "Components/Sprite.hpp"
#include "Registry.hpp"
#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class ParalaxSystem : public ISystems {
            public:
                void operator()(Registry &r) {
                    auto &paralax = r.get_components<ecs::component::Parallax>();
                    auto &positions = r.get_components<ecs::component::Position>();
                    auto &animation = r.get_components<ecs::component::Animations>();

                    for (std::size_t i = 0; i < positions.size(); ++i) {
                        if (positions[i] && paralax[i]) {
                            if (animation[i]->_clock.getElapsedTime().asMicroseconds() > 0.1) {
                                if (positions[i]->_x <= -1920) {
                                    positions[i]->_x = 1920 * paralax[i]->_multiplicator;
                                }
                                animation[i]->_clock.restart();
                                positions[i]->_x -= paralax[i]->_speed;
                            }
                        }
                    }
                }
        };
    };
};

#endif /* !PARALAXSYSTEM_HPP_ */
