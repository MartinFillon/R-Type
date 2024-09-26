/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** FilledColorComponent
*/

#ifndef FILLEDCOLORCOMPONENT_HPP_
    #define FILLEDCOLORCOMPONENT_HPP_

    #include <SFML/Graphics/Color.hpp>

namespace ecs {
    namespace component {
        struct FilledColorComponent {
            sf::Color _color;
        };
    };
};


#endif /* !FILLEDCOLORCOMPONENT_HPP_ */
