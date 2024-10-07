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

#define HOST 1
#define PORT 2
#define NB_ARGS 3
#define SUCCESS 0
#define ERROR 84

namespace rtype {

    class Gui : ecs::IContext {

        public:

            Gui();

            void setupGame();
            int setupNetwork(const std::string server_ip, const std::string server_port);

            void start();

            int run() override;

            std::shared_ptr<ecs::Registry> &getRegistry() {
                return _r;
            };

            Menu &getMenu()
            {
                return _menu;
            }
            sf::RenderWindow &getWin()
            {
                return _window;
            }
        private:

            Network _network;
            Menu _menu;

            void setupWeapon();
            void setupPlayer();
            void setupCollisons();
            void setupBackground();
            void setupBasicEnnemies();
            void setupDestroy();

            sf::RenderWindow _window;
            std::shared_ptr<ecs::Registry> _r;
            ecs::Clock _drawClock;
            ecs::Clock _systemClock;
            ecs::ComponentFactory _factory;

    };

};

#endif /* !GUI_HPP_ */
