/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Gui
*/

#include "../include/Gui.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include "Components/Animations.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Sprite.hpp"
#include "ZipperIterator.hpp"

street_fighter::Gui::Gui(Game &game): _game(game), _window(sf::RenderWindow(sf::VideoMode(1920, 1080), SECOND_GAME_NAME))
{
}

int street_fighter::Gui::run()
{
    auto &positions = _game._r.get_components<ecs::component::Position>();
    auto &animations = _game._r.get_components<ecs::component::Animations>();
    auto &sprites = _game._r.get_components<ecs::component::Sprite>();
    auto &drawable = _game._r.get_components<ecs::component::Drawable>();

    while (_window.isOpen()) {
        sf::Event event;

        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }

        _window.clear(sf::Color::Black);

        for (auto &&[pos, anim, spri, draw] : ecs::custom_zip(positions, animations, sprites, drawable)) {
            if (!pos || !anim || !spri || !draw) {
                continue;
            }
            sf::Texture texture;
            texture.loadFromFile(spri->_pathToSprite);
            sf::Sprite sprite;
            sprite.setTexture(texture);
            if (draw->_drawable) {
                _window.draw(sprite);
            }
        }
    }
    return EXIT_SUCCESS;
}
