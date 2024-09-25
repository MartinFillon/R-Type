/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Context
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ECS {

class Context {
  public:
    Context(sf::RenderWindow &);
    ~Context();

    sf::RenderWindow &getRenderWindow();

  protected:
  private:
    sf::RenderWindow &_window;
};
} // namespace ECS
