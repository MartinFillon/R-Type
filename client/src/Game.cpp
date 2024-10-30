/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Game file
*/

#include "Game.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <exception>
#include <memory>
#include <spdlog/spdlog.h>
#include "ComponentFactory.hpp"
#include "Protocol.hpp"
#include "RegistryWrapper.hpp"
#include "Systems/DestroySystem.hpp"
#include "Systems/ParallaxSystem.hpp"
#include "TextureManager.hpp"

namespace rtype::client {
    Game::Game(sf::RenderWindow &window, Network &network)
        : _gameShotSoundBuffer(SHOOT_SOUND), _gameMusicBuffer(GAME_MUSIC), _window(window),
          _gameSound(_gameMusicBuffer), _shotSound(_gameShotSoundBuffer),
          _textureManager([this](std::string path) { return std::make_shared<sf::Texture>(path); }, PATH_TO_ASSETS),
          _network(network)
    {
        _gameSound.pause();
        _shotSound.pause();
    }

    void Game::setupBackground()
    {
        try {
            _cf->createEntity(_registry->getClientRegistry(), CONFIG_BACKGROUND_0);
            _cf->createEntity(_registry->getClientRegistry(), CONFIG_BACKGROUND_2);
            _cf->createEntity(_registry->getClientRegistry(), CONFIG_BACKGROUND_3);
            _cf->createEntity(_registry->getClientRegistry(), CONFIG_BACKGROUND_4);
            _registry->getClientRegistry()->add_system<ecs::systems::ParalaxSystem>();
        } catch (const ecs::ComponentFactory::ComponentFactoryException &error) {
            spdlog::error("Error on setup Background {}", error.what());
        }
    }

    void Game::setupSound()
    {
        try {
            _gameSound.setLooping(true);
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
        while (const std::optional event = _window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _window.close();
            }
            launchMusic();
            if (const auto *key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->scancode == sf::Keyboard::Scancode::X) {
                    _shotSound.play();
                    _network.send(protocol::Operations::EVENT, {protocol::Events::SHOOT});
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::UP});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::DOWN});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::LEFT});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                _network.send(protocol::Operations::EVENT, {protocol::Events::MOVE, protocol::Direction::RIGHT});
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
