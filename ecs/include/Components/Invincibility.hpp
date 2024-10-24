/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Invincibility
*/

#ifndef INVINCIBILITY_HPP_
#define INVINCIBILITY_HPP_

#include "Clock.hpp"

namespace ecs {
    namespace component {
        struct Invincibility {
            bool _invincible;
            int _time_in_ms;
            ecs::Clock _clock;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !INVINCIBILITY_HPP_ */
