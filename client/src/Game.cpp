/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Game file
*/

#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "Game.hpp"
#include "ComponentFactory.hpp"
#include "Packet.hpp"
#include "Systems/ParallaxSystem.hpp"
#include "ZipperIterator.hpp"

client::Game::Game(sf::RenderWindow &window, Network &network): _window(window), _network(network) {}

void client::Game::setupBackground()
{
    // ecs::ComponentFactory factory(_registry, ecs::ComponentFactory::Mode::Client);
    // factory.createEntity("config/background/background.json");
    // factory.createEntity("config/background/background_2.json");
    // factory.createEntity("config/background/background_3.json");
    // factory.createEntity("config/background/background_4.json");
    // _registry->add_system(ecs::systems::ParalaxSystem());
}

void client::Game::setRegistry(std::shared_ptr<ecs::Registry> registry)
{
    _registry = registry;

    _registry->register_component<ecs::component::Size>();
    _registry->register_component<ecs::component::Sprite>();
    _registry->register_component<ecs::component::Drawable>();
    _registry->register_component<ecs::component::Position>();
    _registry->register_component<ecs::component::Animations>();
}

int client::Game::run()
{
    setupBackground();
    while (_window.isOpen()) {
        event();
        display();
        _registry->run_systems();
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
            std::cerr << "move UP\n";
            _network.send(protocol::Operations::EVENT, { protocol::Events::MOVE, protocol::Direction::UP});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            std::cerr << "move Left\n";
            _network.send(protocol::Operations::EVENT, { protocol::Events::MOVE, protocol::Direction::LEFT});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            std::cerr << "move Right\n";
            _network.send(protocol::Operations::EVENT, { protocol::Events::MOVE, protocol::Direction::RIGHT});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            std::cerr << "move Down\n";
            _network.send(protocol::Operations::EVENT, { protocol::Events::MOVE, protocol::Direction::DOWN});
        }


        // for (auto &move: moves) {
            // if (event.type == sf::Keyboard::isKeyPressed(move.first)) {
            // }
        // }

    }

    return EXIT_SUCCESS;
}

int client::Game::display()
{
    if (_clock.getSeconds() < FRAME_PER_SECONDS(60)) {
        return EXIT_SUCCESS;
    }

    auto &sizes = _registry->get_components<ecs::component::Size>();
    auto &sprites = _registry->get_components<ecs::component::Sprite>();
    auto &drawables = _registry->get_components<ecs::component::Drawable>();
    auto &positions = _registry->get_components<ecs::component::Position>();
    auto &animations = _registry->get_components<ecs::component::Animations>();

    _window.clear();

    for (auto &&[draw, anim, spri, si, pos]: ecs::custom_zip(drawables, animations, sprites, sizes, positions)) {

        if (!draw || !anim || !spri || !si || !pos) {
            continue;
        }

        if (spri->_pathToSprite.empty()) {
            continue;
        }

        sf::Sprite sprite;

        sprite.setPosition(pos->_x, pos->_y);
        sprite.setScale(si->_width, si->_height);
        sprite.setTexture(_textureManager.getTexture(spri->_pathToSprite));
        sprite.setTextureRect(sf::IntRect(anim->_x, anim->_y, anim->_width, anim->_height));

        _window.draw(sprite);
    }

    _clock.restart();
    _window.display();

    return EXIT_SUCCESS;
}