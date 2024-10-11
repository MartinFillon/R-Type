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
#include "IContext.hpp"
#include "Menu.hpp"
#include "Network.hpp"
#include "Registry.hpp"
#include "RegistryWrapper.hpp"

#define ERROR 84
#define SUCCESS 0

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

namespace client {

    class Gui : ecs::IContext {

      public:
        Gui();

        int run();

      private:
        sf::RenderWindow _window;

        Network _network;

        Menu _menu;
        Game _game;

        std::shared_ptr<rtype::RegistryWrapper> _registry;
    };

}; // namespace client

#endif /* !GUI_HPP_ */
