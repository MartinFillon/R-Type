/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** OutlinedColor
*/

#ifndef OUTLINEDCOLOR_HPP_
#define OUTLINEDCOLOR_HPP_

namespace ecs {
    namespace component {
        /// @brief OutlinedColor Component with double for r, g, b, a to stored the color with his transparency
        struct OutlinedColor {
            double _r;
            double _g;
            double _b;
            double _a;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !OUTLINEDCOLOR_HPP_ */
