/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Gui
*/

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include <iostream>
#include "../include/Gui.hpp"
#include "Components/Animations.hpp"
#include "Components/Drawable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "ZipperIterator.hpp"

street_fighter::Gui::Gui(Game &game): _game(game), _window(sf::VideoMode(1920, 1080), SECOND_GAME_NAME)
{
}

int street_fighter::Gui::handleEvents()
{
    sf::Event event;
    auto &keys = _game._r.get_components<ecs::component::KeyPressed>();

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }

        if (event.key.code == sf::Keyboard::Up) {
            keys[_game.findPlayerIndex().getId()]->_value = ecs::component::Key::Up;
        }

        if (event.key.code == sf::Keyboard::Down) {
            keys[_game.findPlayerIndex().getId()]->_value = ecs::component::Key::Down;
        }

        if (event.key.code == sf::Keyboard::Left) {
            keys[_game.findPlayerIndex().getId()]->_value = ecs::component::Key::Left;
        }

        if (event.key.code == sf::Keyboard::Right) {
            keys[_game.findPlayerIndex().getId()]->_value = ecs::component::Key::Right;
        }

    }

    return EXIT_SUCCESS;
}

void street_fighter::Gui::display()
{
    auto &positions = _game._r.get_components<ecs::component::Position>();
    auto &animations = _game._r.get_components<ecs::component::Animations>();
    auto &sprites = _game._r.get_components<ecs::component::Sprite>();
    auto &drawable = _game._r.get_components<ecs::component::Drawable>();
    auto &sizes = _game._r.get_components<ecs::component::Size>();

    for (auto &&[pos, anim, spri, draw, size] : ecs::custom_zip(positions, animations, sprites, drawable, sizes)) {
        if (!pos || !anim || !spri || !draw || !size || !draw->_drawable) {
            continue;
        }

        sf::Texture texture;
        if (!texture.loadFromFile(spri->_pathToSprite)) {
            std::cerr << "Error on loading sprite: " << spri->_pathToSprite << "\n";
        }
        sf::Sprite sprite;
        sprite.setPosition(pos->_x, pos->_y);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(anim->_x, anim->_y, anim->_width, anim->_height));
        sprite.setScale(size->_width, size->_height);
        _window.draw(sprite);
    }
}

int street_fighter::Gui::run()
{
    while (_window.isOpen()) {
        handleEvents();
        _window.clear(sf::Color::Black);
        display();
        _game.run();
        _window.display();
    }
    return EXIT_SUCCESS;
}
