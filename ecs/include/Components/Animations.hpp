/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animations
*/

#ifndef ANIMATIONS_HPP_
#define ANIMATIONS_HPP_

#include <string>
#include "Clock.hpp"
#include "IComponent.hpp"

namespace ecs {
    namespace component {

        struct Animations : public IComponent {
            Animations() = default;
            Animations(ecs::Clock clock, int width, int height, int x, int y, int rotation = 0): _clock(clock), _width(width), _height(height), _x(x), _y(y), _rotation(rotation) {}
            ecs::Clock _clock;
            int _width;
            int _height;
            int _x;
            int _y;
            int _rotation;
            std::string _name = "Animations";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ANIMATIONS_HPP_ */
