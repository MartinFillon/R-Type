/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Color : public IComponent {
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a): _r(r), _g(g), _b(b), _a(a) {}
            Color() = default;
            unsigned char _r;
            unsigned char _g;
            unsigned char _b;
            unsigned char _a;
            std::string _name = "Color";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !COLOR_HPP_ */
