/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Clock.hpp"
#include "Network.hpp"
#include "IContext.hpp"
#include "Registry.hpp"
#include "ComponentFactory.hpp"
#include "Menu.hpp"
#include "TextureManager.hpp"
#include "GameClient.hpp"

#define FRAME_PER_SECONDS(x) (int)(1 / x)
#define HOST 1
#define PORT 2
#define NB_ARGS 3
#define SUCCESS 0
#define ERROR 84

namespace rtype {

    class Gui : ecs::IContext {

        public:

            Gui();

            int setupNetwork(const std::string server_ip, const std::string server_port);

            void start();

            std::shared_ptr<ecs::Registry> &getRegistry() {
                return _r;
            };

            Menu &getMenu()
            {
                return _menu;
            }
            int run();

            sf::RenderWindow &getWindow()
            {
                return _window;
            }
            void setupGameThread();

        private:
            sf::RenderWindow _window;
            std::shared_ptr<ecs::Registry> _r;
            ecs::Clock _drawClock;
            ecs::Clock _systemClock;
            TextureManager _textureManager;
            ecs::Clock _gameTimer;
            ecs::ComponentFactory _factory;
            Network _network;
            Menu _menu;
            GameClient _game;
            sf::Thread _gameThread;
    };

};

#endif /* !GUI_HPP_ */
