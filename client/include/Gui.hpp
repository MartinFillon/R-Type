/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

#include "ComponentFactory.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Network.hpp"
#include "RegistryWrapper.hpp"

#define GAME_NAME "R-Type"

#define R_ERROR 84
#define SUCCESS 0
#define QUIT_PRESS 0

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

namespace rtype::client {

    class Gui {

      public:
        Gui();

        int run();

      private:
        sf::RenderWindow _window;

        Network _network;

        Menu _menu;
        Game _game;

        std::shared_ptr<RegistryWrapper> _registry;
        std::shared_ptr<ecs::ComponentFactory> _cf;
    };

}; // namespace rtype::client
#endif /* !GUI_HPP_ */
