/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <SFML/Graphics/Text.hpp>
#include <string>
#include "./Size.hpp"

namespace ecs {
    namespace component {
        struct Text {
            std::string _string;
            sf::Text _text;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !TEXT_HPP_ */
