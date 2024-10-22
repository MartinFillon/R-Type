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

#include "../include/Gui.hpp"
#include "Components/Animations.hpp"
#include "Components/Drawable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Game.hpp"
#include "ZipperIterator.hpp"

street_fighter::Gui::Gui(Game &game): _game(game), _textureManager([this](std::string path){sf::Texture texture; texture.loadFromFile(path); return std::make_shared<sf::Texture>(texture); }, PATH_TO_STREET_FIGHTER_ASSETS), _window(sf::VideoMode(1920, 1080), SECOND_GAME_NAME)
{
}

int street_fighter::Gui::handleEvents()
{
    sf::Event event;
    auto &keys = _game._r.get_components<ecs::component::KeyPressed>();
    auto &anim = _game._r.get_components<ecs::component::Animations>();

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }

        if (event.key.code == sf::Keyboard::Up) {
            keys[_game.findPlayerIndex().getId()]->_value = ecs::component::Key::Up;
            anim[_game.findPlayerIndex().getId()]->_width = JUMP_ANIMATION_WIDTH;
            anim[_game.findPlayerIndex().getId()]->_height = JUMP_ANIMATION_HEIGHT;
            anim[_game.findPlayerIndex().getId()]->_x = JUMP_ANIMATION_X;
            anim[_game.findPlayerIndex().getId()]->_y = JUMP_ANIMATION_Y;
        }

        if (event.key.code == sf::Keyboard::Down) {
            keys[_game.findPlayerIndex().getId()]->_value = ecs::component::Key::Down;
            anim[_game.findPlayerIndex().getId()]->_x = SIT_ANIMATION_X;
            anim[_game.findPlayerIndex().getId()]->_y = SIT_ANIMATION_Y;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            keys[_game.findPlayerIndex().getId()]->_value = ecs::component::Key::Left;
            anim[_game.findPlayerIndex().getId()]->_width = INIT_WIDTH;
            anim[_game.findPlayerIndex().getId()]->_height = INIT_HEIGHT;
            anim[_game.findPlayerIndex().getId()]->_x = INIT_X;
            anim[_game.findPlayerIndex().getId()]->_y = INIT_Y;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            keys[_game.findPlayerIndex().getId()]->_value = ecs::component::Key::Right;
            anim[_game.findPlayerIndex().getId()]->_width = INIT_WIDTH;
            anim[_game.findPlayerIndex().getId()]->_height = INIT_HEIGHT;
            anim[_game.findPlayerIndex().getId()]->_x = INIT_X;
            anim[_game.findPlayerIndex().getId()]->_y = INIT_Y;
        }

    }

    return EXIT_SUCCESS;
}

void street_fighter::Gui::display()
{
    if (_gameClock.getSeconds() < FRAME_DURATION(60)) {
        return;
    }
    _gameClock.restart();
    auto &positions = _game._r.get_components<ecs::component::Position>();
    auto &animations = _game._r.get_components<ecs::component::Animations>();
    auto &sprites = _game._r.get_components<ecs::component::Sprite>();
    auto &drawable = _game._r.get_components<ecs::component::Drawable>();
    auto &sizes = _game._r.get_components<ecs::component::Size>();

    for (auto &&[pos, anim, spri, draw, size] : ecs::custom_zip(positions, animations, sprites, drawable, sizes)) {
        if (!pos || !anim || !spri || !draw || !size || !draw->_drawable) {
            continue;
        }
        auto texture = _textureManager.getTexture(spri->_pathToSprite);
        sf::Sprite sprite;
        sprite.setPosition(pos->_x, pos->_y);
        sprite.setTexture(*texture);
        sprite.setTextureRect(sf::IntRect(anim->_x, anim->_y, anim->_width, anim->_height));
        sprite.setScale(size->_width, size->_height);
        _window.draw(sprite);
    }
}

int street_fighter::Gui::run()
{
    while (_window.isOpen()) {
        _window.clear(sf::Color::Black);
        handleEvents();
        display();
        _game.run();
        _gameClock.restart();
        _window.display();
    }
    return EXIT_SUCCESS;
}
