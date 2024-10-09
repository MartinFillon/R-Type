/*
** EPITECH PROJECT, 2024
** R type
** File description:
** GameClient class
*/

#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Clock.hpp"
#include "ComponentFactory.hpp"
#include "TextureManager.hpp"

#define FRAME_PER_SECONDS(x) (int)(1 / x)

namespace rtype {
    class GameClient {
      public:
        GameClient(sf::RenderWindow &window);
        ~GameClient() = default;

        void setupGame();
        void setupWeapon();
        void setupPlayer();
        void setupCollisons();
        void setupBackground();
        void setupBasicEnnemies();
        void setupBosses();
        void setupDestroy();
        int run();

      private:
        sf::RenderWindow &_gameWin;

        ecs::Clock _drawClock;
        ecs::Clock _gameTimer;
        TextureManager _textureManager;
    };
} // namespace rtype

#endif /* !GAMECLIENT_HPP_ */
