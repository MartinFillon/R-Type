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
        _r(std::make_shared<ecs::Registry>()),_menu(_window), _game(_window, _r),
        _gameThread(&rtype::Gui::start, this)
    {
        _menu.setupMenu();
        _network.setRegistry(_r);
    }

    int Gui::setupNetwork(const std::string server_ip, const std::string server_port)
    {
        if (_network.setup(server_ip, server_port)) {
            return EXIT_FAILURE;
        }
        setupGameThread();
        // potentiellement ici le thread network
        return EXIT_SUCCESS;
    }

    int Gui::run()
    {
        _game.run();
        return EXIT_SUCCESS;
    }

    void Gui::setupGameThread()
    {
        _window.setActive(false);
        _gameThread.launch();
        _gameThread.wait();
    }
    void Gui::start()
    {
        _game.run();
    }

} // namespace rtype
