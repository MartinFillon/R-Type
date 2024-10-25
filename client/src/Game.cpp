/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Game file
*/

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <exception>
#include <memory>
#include <iostream>
#include <spdlog/spdlog.h>
#include "ComponentFactory.hpp"
#include "Game.hpp"
#include "Protocol.hpp"
#include "RegistryWrapper.hpp"
#include "Systems/DestroySystem.hpp"
#include "Systems/ParallaxSystem.hpp"
#include "TextureManager.hpp"

namespace rtype::client {
    Game::Game(sf::RenderWindow &window, Network &network)
        : _window(window), _textureManager(
                               [this](std::string path) {
                                   sf::Texture texture;
                                   texture.loadFromFile(path);
                                   return std::make_shared<sf::Texture>(texture);
                               },
                               PATH_TO_ASSETS
                           ),
          _network(network)
    {
    }

    void Game::setupBackground()
    {
        try {
            _cf->createEntity(_registry->getClientRegistry(), CONFIG_BACKGROUND_0);
            _cf->createEntity(_registry->getClientRegistry(), CONFIG_BACKGROUND_2);
            _cf->createEntity(_registry->getClientRegistry(), CONFIG_BACKGROUND_3);
            _cf->createEntity(_registry->getClientRegistry(), CONFIG_BACKGROUND_4);
            _registry->getClientRegistry()->add_system(ecs::systems::ParalaxSystem());
        } catch (const ecs::ComponentFactory::ComponentFactoryException &error) {
            spdlog::error("Error on setup Background {}", error.what());
        }
    }

    void Game::setupSound()
    {
        try {
            _gameShotSoundBuffer.loadFromFile(SHOOT_SOUND);
            _gameMusicBuffer.loadFromFile(GAME_MUSIC);

            _shotSound.setBuffer(_gameShotSoundBuffer);
            _gameSound.setBuffer(_gameMusicBuffer);

            _gameSound.setLoop(true);
        } catch (const std::exception &e) {
            spdlog::error("Error on setup Sound {}", e.what());
        }
    }

    void Game::setRegistry(std::shared_ptr<RegistryWrapper> &registry)
    {
        _registry = registry;
    }

    int Game::run()
    {
        _registry->getServerRegistry()->add_system<ecs::systems::DestroySystem>();
        setupBackground();
        setupSound();
        while (_window.isOpen()) {
            event();
            display();
            _registry->run_systems(*_cf, nullptr);
        }
        _network.send(protocol::Operations::LEAVING, {});
        _network.stop();
        return EXIT_SUCCESS;
    }

    void Game::launchMusic()
    {
        if (_gameSound.getStatus() != sf::SoundSource::Status::Playing) {
            _gameSound.play();
        }
    }

    void Game::event()
    {
        sf::Event event;

        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
            launchMusic();
        }
        if (event.key.code == sf::Keyboard::X) {
            _shotSound.play();
            _network.send(protocol::Operations::EVENT, {protocol::Events::SHOOT});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::UP});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::DOWN});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::LEFT});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::RIGHT});
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
