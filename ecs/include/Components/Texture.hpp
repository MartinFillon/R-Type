/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
    #define TEXTURE_HPP_

    #include <SFML/Graphics/Texture.hpp>

namespace ecs {
    namespace component {
        struct Texture {
            sf::Texture _texture;
        };
    };
};

#endif /* !TEXTURE_HPP_ */
