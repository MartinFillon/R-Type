/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Context
*/

#include <SFML/Graphics/RenderWindow.hpp>

#include "Context.hpp"

namespace ecs {

Context::Context(sf::RenderWindow &window) : _window(window)
{
    return;
}

Context::~Context()
{
    return;
}

sf::RenderWindow &Context::getRenderWindow()
{
    return _window;
}

} // namespace ecs
