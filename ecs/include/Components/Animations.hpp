/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animations
*/

#ifndef ANIMATIONS_HPP_
#define ANIMATIONS_HPP_

#include "Clock.hpp"

namespace ecs {
    namespace component {
        enum Object { Background, Player, Weapon, Ennemies, InDestroy };

        enum Type { None, Basic, Milespates, Boss, First, Second };

        struct Animations {
            ecs::Clock _clock;
            int _width;
            int _height;
            int _x;
            int _y;
            int _rotation;
            Object _object;
            Type _type;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ANIMATIONS_HPP_ */
