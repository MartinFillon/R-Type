/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RectangleShape
*/

#ifndef RECTANGLESHAPE_HPP_
#define RECTANGLESHAPE_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct RectangleShape : public IComponent {
            RectangleShape(int height, int width, int length): _height(height), _width(width), _length(length) {}
            RectangleShape() = default;
            int _height;
            int _width;
            int _length;
            std::string _name = "Rectangle Shape";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs


#endif /* !RECTANGLESHAPE_HPP_ */
