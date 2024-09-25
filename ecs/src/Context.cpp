/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Context
*/

#include "Context.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace ECS {

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

} // namespace ECS
