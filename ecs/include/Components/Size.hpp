/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Size
*/

#ifndef SIZE_HPP_
#define SIZE_HPP_

namespace ecs {
    namespace component {
        /// @brief Size component, store the double in width and height as a double for the size, 1 is the sprite size to upgrade it put it superior to 1, to decrease it, inferior to 1
        struct Size {
            double _width;
            double _height;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SIZE_HPP_ */
