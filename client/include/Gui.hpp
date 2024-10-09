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
#include "ComponentFactory.hpp"
#include "GameClient.hpp"
#include "IContext.hpp"
#include "Menu.hpp"
#include "Network.hpp"
#include "Registry.hpp"

#define HOST 1
#define PORT 2
#define NB_ARGS 3
#define SUCCESS 0

// #define ERROR 84

namespace rtype {

    class Gui : ecs::IContext {

      public:
        Gui();

        int setupNetwork(const std::string server_ip, const std::string server_port);
        Menu &getMenu()
        {
            return _menu;
        }

        int run();
        int runNetwork();

        sf::RenderWindow &getWindow()
        {
            return _window;
        }

      private:
        sf::RenderWindow _window;
        Network _network;
        Menu _menu;
        GameClient _game;
    };

}; // namespace rtype

#endif /* !GUI_HPP_ */
