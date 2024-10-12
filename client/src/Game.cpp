/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Game file
*/

#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "ComponentFactory.hpp"
#include "Game.hpp"
#include "Protocol.hpp"
#include "RegistryWrapper.hpp"
#include "Systems/DestroySystem.hpp"
#include "Systems/ParallaxSystem.hpp"

namespace rtype::client {
    Game::Game(sf::RenderWindow &window, Network &network) : _window(window), _network(network) {}

    void Game::setupBackground()
    {
        ecs::ComponentFactory factory(_registry->getClientRegistry(), ecs::ComponentFactory::Mode::Client);
        factory.createEntity("config/background/background.json");
        factory.createEntity("config/background/background_2.json");
        factory.createEntity("config/background/background_3.json");
        factory.createEntity("config/background/background_4.json");
        _registry->getClientRegistry()->add_system(ecs::systems::ParalaxSystem());
    }

    void Game::setRegistry(std::shared_ptr<RegistryWrapper> &registry)
    {
        _registry = registry;
    }

    int Game::run()
    {
        _registry->getServerRegistry()->add_system(ecs::systems::DestroySystem());
        setupBackground();
        while (_window.isOpen()) {
            event();
            display();
            _registry->run_systems(nullptr);
        }
        _network.send(protocol::Operations::LEAVING, {});
        _network.stop();
        return EXIT_SUCCESS;
    }

    void Game::event()
    {
        sf::Event event;

        while (_window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                _window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (moves.find(event.key.code) != moves.end()) {
                    _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, moves[event.key.code]});
                }

                if (event.key.code == sf::Keyboard::X) {
                    _network.send(protocol::Operations::EVENT, {protocol::Events::SHOOT});
                }
            }
        }
    }

    void Game::display()
    {
        if (_clock.getSeconds() < FRAME_PER_SECONDS(60)) {
            return;
        }

        _window.clear();

        _registry->draw(_window, _textureManager);

        _clock.restart();
        _window.display();

        return;
    }
} // namespace rtype::client
