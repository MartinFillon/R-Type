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
#include <cstddef>
#include <cstdlib>
#include <spdlog/spdlog.h>

#include "Components/Animations.hpp"
#include "Components/Drawable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Game.hpp"
#include "Gui.hpp"
#include "ZipperIterator.hpp"

street_fighter::Gui::Gui()
    : _game(), _textureManager(
                   [this](std::string path) { return std::make_shared<sf::Texture>(path); },
                   PATH_TO_STREET_FIGHTER_ASSETS
               ),
      _window(sf::VideoMode({1920, 1080}), SECOND_GAME_NAME)
{
}

int street_fighter::Gui::handleEvents()
{
    auto &keys = _game._r->get_components<ecs::component::KeyPressed>();
    auto &anim = _game._r->get_components<ecs::component::Animations>();
    auto &pos = _game._r->get_components<ecs::component::Position>();
    const std::size_t playerIndex = _game.findPlayerIndex().getId();


    if (_game.getIsCinematic()) {
        return EXIT_SUCCESS;
    }
    while (const std::optional event = _window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            _window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
            keys[playerIndex]->_value = ecs::component::Key::Up;
            anim[playerIndex]->_width = JUMP_ANIMATION_WIDTH;
            anim[playerIndex]->_height = JUMP_ANIMATION_HEIGHT;
            anim[playerIndex]->_x = JUMP_ANIMATION_X;
            anim[playerIndex]->_y = JUMP_ANIMATION_Y;
            pos[playerIndex]->_y = NORMAL_Y_POSITION;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
            keys[playerIndex]->_value = ecs::component::Key::Down;
            anim[playerIndex]->_x = SIT_ANIMATION_X;
            anim[playerIndex]->_y = SIT_ANIMATION_Y;
            anim[playerIndex]->_width = SIT_ANIMATION_WIDTH;
            anim[playerIndex]->_height = SIT_ANIMATION_HEIGHT;
            pos[playerIndex]->_y = SIT_POSITION_Y;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
            keys[playerIndex]->_value = ecs::component::Key::Left;
            pos[playerIndex]->_y = NORMAL_Y_POSITION;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
            keys[playerIndex]->_value = ecs::component::Key::Right;
            pos[playerIndex]->_y = NORMAL_Y_POSITION;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X)) {
            if (keys[playerIndex]->_value != ecs::component::Key::Up) {
                pos[playerIndex]->_y = NORMAL_Y_POSITION;
            }
            keys[playerIndex]->_value = ecs::component::Key::Punch;
            anim[playerIndex]->_width = PUNCH_ANIMATION_WIDTH;
            anim[playerIndex]->_height = PUNCH_ANIMATION_HEIGHT;
            anim[playerIndex]->_x = PUNCH_ANIMATION_X;
            anim[playerIndex]->_y = PUNCH_ANIMATION_Y;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
            keys[playerIndex]->_value = ecs::component::Key::Kick;
            anim[playerIndex]->_width = KICK_ANIMATION_WIDTH;
            anim[playerIndex]->_height = KICK_ANIMATION_HEIGHT;
            anim[playerIndex]->_x = KICK_ANIMATION_X;
            anim[playerIndex]->_y = KICK_ANIMATION_Y;
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
    auto &positions = _game._r->get_components<ecs::component::Position>();
    auto &animations = _game._r->get_components<ecs::component::Animations>();
    auto &sprites = _game._r->get_components<ecs::component::Sprite>();
    auto &drawable = _game._r->get_components<ecs::component::Drawable>();
    auto &sizes = _game._r->get_components<ecs::component::Size>();

    for (auto &&[pos, anim, spri, draw, size] : ecs::custom_zip(positions, animations, sprites, drawable, sizes)) {
        if (!pos || !anim || !spri || !draw || !size || !draw->_drawable) {
            continue;
        }
        try {
            auto texture = _textureManager.getTexture(spri->_pathToSprite);
            sf::Sprite sprite(*texture, sf::IntRect({(anim->_x), (anim->_y)}, {(anim->_height), (anim->_width)}));
            sprite.setPosition({static_cast<float>(pos->_x), static_cast<float>(pos->_y)});
            sprite.setTexture(*texture);
            sprite.setScale({static_cast<float>(size->_height), static_cast<float>(size->_width)});
            _window.draw(sprite);
        } catch (const ecs::TextureManager<sf::Texture>::TextureManagerException &error) {
            spdlog::error("Could not display {}", error.what());
        }
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
