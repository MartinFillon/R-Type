/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
    #define SPRITE_HPP_

    #include <SFML/Graphics/Sprite.hpp>

namespace ecs {
    namespace component {
        struct Sprite {
            sf::Sprite _sprite;
        };
    };
};

#endif /* !SPRITE_HPP_ */
