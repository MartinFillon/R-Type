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
#include "Network.hpp"
#include "IContext.hpp"
#include "Registry.hpp"
#include "ComponentFactory.hpp"

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
            void setupDestroy();
            int run();

        private:

            sf::RenderWindow &_gameWin;

            ecs::Clock _drawClock;
            ecs::Clock _systemClock;
            ecs::ComponentFactory _factory;
            std::shared_ptr<ecs::Registry> _r;
    };
}

#endif /* !GAMECLIENT_HPP_ */
