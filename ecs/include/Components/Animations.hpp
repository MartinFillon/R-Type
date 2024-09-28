/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animations
*/

#ifndef ANIMATIONS_HPP_
#define ANIMATIONS_HPP_

#include <SFML/System/Clock.hpp>

namespace ecs {
    namespace component {
        enum Object { Background, Player, Weapon };

        struct Animations {
            sf::Clock _clock;
            double _width;
            double _height;
            double _x;
            double _y;
            double _rotation;
            Object _object;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ANIMATIONS_HPP_ */
