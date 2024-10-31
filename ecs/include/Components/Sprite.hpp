/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct Sprite {
            std::string _pathToSprite;
            std::string _name = "Sprite";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SPRITE_HPP_ */
