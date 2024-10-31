/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <string>
#include "Components/IComponent.hpp"

namespace ecs {
    namespace component {
        struct Sprite : public IComponent {
            Sprite(std::string pathToSprite): _pathToSprite(pathToSprite) {}
            Sprite() = default;
            std::string _pathToSprite;
            std::string _name = "Sprite";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SPRITE_HPP_ */
