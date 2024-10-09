/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animations
*/

#ifndef ANIMATIONS_HPP_
#define ANIMATIONS_HPP_

#include <SFML/System/Clock.hpp>
#include "Clock.hpp"

namespace ecs {
    namespace component {
        enum Object { Background, Player, Weapon, Ennemies, InDestroy };

        enum Type { None, Basic, Milespates, Boss };

        struct Animations {
            ecs::Clock _clock;
            double _width;
            double _height;
            double _x;
            double _y;
            double _rotation;
            Object _object;
            Type _type;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ANIMATIONS_HPP_ */
