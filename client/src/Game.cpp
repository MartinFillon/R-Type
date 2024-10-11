/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Game file
*/

#include <SFML/Window/Keyboard.hpp>

#include "ComponentFactory.hpp"
#include "Game.hpp"
#include "RegistryWrapper.hpp"
#include "Systems/DestroySystem.hpp"
#include "Systems/ParallaxSystem.hpp"

client::Game::Game(sf::RenderWindow &window, Network &network) : _window(window), _network(network) {}

void client::Game::setupBackground()
{
    ecs::ComponentFactory factory(_registry->getClientRegistry(), ecs::ComponentFactory::Mode::Client);
    factory.createEntity("config/background/background.json");
    factory.createEntity("config/background/background_2.json");
    factory.createEntity("config/background/background_3.json");
    factory.createEntity("config/background/background_4.json");
    _registry->getClientRegistry()->add_system(ecs::systems::ParalaxSystem());
}

void client::Game::setRegistry(std::shared_ptr<rtype::RegistryWrapper> &registry)
{
    _registry = registry;
}

int client::Game::run()
{
    _registry->getServerRegistry()->add_system(ecs::systems::DestroySystem());
    setupBackground();
    while (_window.isOpen()) {
        event();
        display();
        _registry->getClientRegistry()->run_systems(nullptr);
        _registry->getServerRegistry()->run_systems(nullptr);
    }

    return EXIT_SUCCESS;
}

int client::Game::event()
{
    sf::Event event;

    while (_window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            _window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::UP});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::LEFT});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::RIGHT});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::DOWN});
        }
    }

    return EXIT_SUCCESS;
}

int client::Game::display()
{
    if (_clock.getSeconds() < FRAME_PER_SECONDS(60)) {
        return EXIT_SUCCESS;
    }

    _window.clear();

    _registry->draw(_window, _textureManager);

    _clock.restart();
    _window.display();

    return EXIT_SUCCESS;
}
