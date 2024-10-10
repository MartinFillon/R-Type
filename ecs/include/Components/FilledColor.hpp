/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** FilledColorComponent
*/

#ifndef FILLEDCOLOR_HPP_
#define FILLEDCOLOR_HPP_

namespace ecs {
    namespace component {
        /// @brief FilledColor Component with double for r, g, b, a to stored the color with his transparency
        struct FilledColor {
            double _r;
            double _g;
            double _b;
            double _a;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !FILLEDCOLOR_HPP_ */
