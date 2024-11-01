/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Size
*/

#ifndef SIZE_HPP_
#define SIZE_HPP_

#include <sstream>
#include <string>
#include "Components/IComponent.hpp"

namespace ecs {
    namespace component {
        struct Size : public IComponent {
            Size(double width, double height): _width(width), _height(height) {}
            Size() = default;
            double _width;
            double _height;
            std::string _name = "Size";
            std::string getName() const {
                return _name;
            }
            std::string getInfo() const {
                std::ostringstream stream;

                stream << "Width: " << _width << " Height: " << _height;

                return stream.str();
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SIZE_HPP_ */
