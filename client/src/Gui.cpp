/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#include "Gui.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <spdlog/spdlog.h>
#include "ComponentFactory.hpp"
#include "Gui.hpp"
#include "RegistryWrapper.hpp"
#include "TCPCommunication.hpp"

namespace rtype::client {
    Gui::Gui()
        : _window(sf::VideoMode({WIN_WIDTH, WIN_HEIGHT}), GAME_NAME), _network(), _menu(_window),
          _game(_window, _network), _lobby(_window)
    {
        try {
            _tcpCommunication = std::make_shared<TCPCommunication>();
            _registry = std::make_shared<RegistryWrapper>();
            _cf = std::make_shared<ecs::ComponentFactory>();
        } catch (const std::bad_alloc &e) {
            spdlog::error("Bad allocation on registry and component factory of the GUI {}", e.what());
        }
    }

    int Gui::handleConnection()
    {
        _quitPress = 0;
        std::string address = _menu.launchMenu();
        std::string ip = address.substr(0, address.find(':'));
        std::string port = address.substr(address.find(':') + 1);

        if (ip.empty() || port.empty()) {
            _quitPress += 1;
            return QUIT_PRESS;
        }

        if (_tcpCommunication.get()->setup(ip, port) == ERROR) {
            return ERROR;
        }

        int UDPport = _lobby.launchLobby(_tcpCommunication);

        if (UDPport == QUIT_PRESS) {
            _quitPress += 1;
            return SUCCESS;
        }

        if (_network.setup(ip, std::to_string(UDPport)) == ERROR) {
            return ERROR;
        }
        return SUCCESS;
    }

    int Gui::run()
    {
        int ret_value = handleConnection();

        if (_quitPress) {
            return SUCCESS;
        }

        if (ret_value) {
            return ERROR;
        }
        spdlog::debug("Network setup done");
        _game.setRegistry(_registry);
        _game.setFactory(_cf);
        _network.setRegistry(_registry->getServerRegistry());
        _network.setFactory(_cf);

        spdlog::debug("Game setup done");
        std::thread network = std::thread(&client::Network::run, std::ref(_network));

        spdlog::debug("Network thread started");
        _game.run();

        network.join();

        return SUCCESS;
    }
} // namespace rtype::client
