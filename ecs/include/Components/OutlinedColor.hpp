/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** OutlinedColor
*/

#ifndef OUTLINEDCOLOR_HPP_
#define OUTLINEDCOLOR_HPP_

#include <SFML/Graphics/Color.hpp>

namespace ecs {
    namespace component {
        struct OutlinedColor {
            sf::Color _outlinedColor;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !OUTLINEDCOLOR_HPP_ */
