/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Gui
*/

#include "../include/Gui.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>

street_fighter::Gui::Gui(Game &game): _game(game), _window(sf::RenderWindow(sf::VideoMode(1920, 1080), SECOND_GAME_NAME))
{
}

int street_fighter::Gui::run()
{
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }
        _window.clear();
    }
    return EXIT_SUCCESS;
}
