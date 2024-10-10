/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#include "Gui.hpp"

client::Gui::Gui(): ecs::IContext(), _window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), GAME_NAME), _network(), _menu(_window), _game(_window, _network)
{
    _registry = std::make_shared<ecs::Registry>();
}

int client::Gui::run()
{
    std::string address = _menu.launchMenu();
    std::string ip = address.substr(0, address.find(':'));
    std::string port = address.substr(address.find(':') + 1);

    if (_network.setup(ip, port) == ERROR) {
        return ERROR;
    }

    _game.setRegistry(_registry);
    _network.setRegistry(_registry);

    std::thread network = std::thread(&client::Network::run, std::ref(_network));

    _game.run();

    network.join();

    return SUCCESS;
}
