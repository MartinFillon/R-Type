/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Size
*/

#ifndef SIZE_HPP_
#define SIZE_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct Size {
            double _width;
            double _height;
            std::string _name = "Size";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SIZE_HPP_ */
