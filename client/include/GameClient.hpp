/*
** EPITECH PROJECT, 2024
** R type
** File description:
** GameClient class
*/

#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_
#include "TextureManager.hpp"
#define FRAME_PER_SECONDS(x) (int)(1 / x)

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Clock.hpp"
#include "ComponentFactory.hpp"
#include "Registry.hpp"

namespace rtype {
    class GameClient {
      public:
        GameClient(sf::RenderWindow &window, std::shared_ptr<ecs::Registry> r);
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
        ecs::Clock _systemClock;
        ecs::Clock _gameTimer;
        TextureManager _textureManager;
        ecs::ComponentFactory _factory;
        std::shared_ptr<ecs::Registry> _r;
    };
} // namespace rtype

#endif /* !GAMECLIENT_HPP_ */
