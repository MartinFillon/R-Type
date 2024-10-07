/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#include "Clock.hpp"
#include "ComponentFactory.hpp"
#include "Gui.hpp"
#include "ImageResolver.hpp"
#include "Systems/BasicRandomEnnemiesSystem.hpp"
#include "Systems/CollisionsSystem.hpp"
#include "Systems/DestroySystem.hpp"
#include "Systems/EnnemiesMilespatesSystem.hpp"
#include "Systems/GunFireSystem.hpp"
#include "Systems/ParallaxSystem.hpp"
#include "Systems/PlayerMouvementSystem.hpp"
#include "ZipperIterator.hpp"

namespace rtype {

    Gui::Gui()
        : ecs::IContext(), _network(), _window(sf::VideoMode(1920, 1080), GAME_NAME),
          _r(std::make_shared<ecs::Registry>()),_menu(_window), _game(_window, _r)
    {
        _menu.setupMenu();
        _network.setRegistry(_r);
    }

    int Gui::setupNetwork(const std::string server_ip, const std::string server_port)
    {
        if (_network.setup(server_ip, server_port)) {
            return EXIT_FAILURE;
        }
        start();
        return EXIT_SUCCESS;
    }

    void Gui::start()
    {
        std::thread handleNetwork(&rtype::Network::run, std::ref(_network));
        // std::thread handleGame(&rtype::Gui::run, this);

        handleNetwork.join();
        // handleGame.join();
    }

    int Gui::run()
    {
    }

} // namespace rtype
