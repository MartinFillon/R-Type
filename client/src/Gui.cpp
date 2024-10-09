/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#include "Gui.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace rtype {

    Gui::Gui()
        : ecs::IContext(), _network(), _window(sf::VideoMode(1920, 1080), GAME_NAME),
         _menu(_window), _game(_window)
    {
        _menu.setupMenu();
    }

    int Gui::setupNetwork(const std::string server_ip, const std::string server_port)
    {
        if (_network.setup(server_ip, server_port)) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    int Gui::run()
    {
        _game.run();
        return EXIT_SUCCESS;
    }

    int Gui::runNetwork()
    {
        return _network.run();
    }

} // namespace rtype
