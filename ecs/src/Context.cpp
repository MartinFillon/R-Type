/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Context
*/

#include <SFML/Graphics/RenderWindow.hpp>

#include "Context.hpp"

namespace ecs {

    Context::Context() : _window(sf::VideoMode(1920, 1080), GAME_NAME) {}

    Context::~Context()
    {
        return;
    }

    sf::RenderWindow &Context::getRenderWindow()
    {
        return _window;
    }

} // namespace ecs
