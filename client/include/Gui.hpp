/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#ifndef GUI_HPP_
    #define GUI_HPP_

    #include <memory>
    #include <SFML/Graphics.hpp>

    #include "Menu.hpp"
    #include "Game.hpp"
    #include "Network.hpp"
    #include "IContext.hpp"
    #include "Registry.hpp"
    #include "ComponentFactory.hpp"

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

            std::shared_ptr<ecs::Registry> _registry;

    };

};

#endif /* !GUI_HPP_ */
