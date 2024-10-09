/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Game file
*/

#include "GameClient.hpp"
#include <memory>

rtype::GameClient::GameClient(sf::RenderWindow &window) : _gameWin(window)
{
    setupGame();
}

void rtype::GameClient::setupGame()
{
}

int rtype::GameClient::run()
{

    while (_gameWin.isOpen()) {
        sf::Event event;
        while (_gameWin.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _gameWin.close();
            }
        }
        if (_drawClock.getSeconds() > FRAME_PER_SECONDS(60)) {
            _gameWin.clear();

            // %% to network link %%
            // for (auto &&[draws, anim, spri, si, pos] :
            //      ecs::custom_zip(drawables, animations, sprites, size, positions)) {
            //     if (!draws || !anim || !spri || !si || !pos) {
            //         continue;
            //     }
            //     if (spri->_pathToSprite.empty()) {
            //         continue;
            //     }
            //     sf::Sprite sprite;
            //     sprite.setPosition(pos->_x, pos->_y);
            //     sprite.setScale(si->_width, si->_height);
            //     sprite.setTextureRect(sf::IntRect(anim->_x, anim->_y, anim->_width, anim->_height));
            //     sprite.setTexture(_textureManager.getTexture(spri->_pathToSprite));
            //     _gameWin.draw(sprite);
            // }
            _drawClock.restart();
        }
        _gameWin.display();
    }

    return EXIT_SUCCESS;
}
