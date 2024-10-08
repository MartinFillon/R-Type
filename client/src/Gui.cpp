/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#include "Clock.hpp"
#include "ComponentFactory.hpp"
#include "Gui.hpp"
#include <SFML/Graphics/Rect.hpp>

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
          _r(std::make_shared<ecs::Registry>()), _drawClock(ecs::Clock()), _systemClock(ecs::Clock()), _gameTimer(ecs::Clock()), _menu(_window)
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

    void Gui::setupDestroy()
    {
        _r->add_system(ecs::systems::DestroySystem());
    }

    void Gui::setupWeapon()
    {
        _r->add_system(ecs::systems::GunFireSystem());
    }

    void Gui::setupPlayer()
    {
        _factory.createEntity("config/player.json");
        _r->add_system(ecs::systems::PlayerMouvementSystem());
    }

    void Gui::setupCollisons()
    {
        _r->add_system(ecs::systems::CollisionsSystem());
    }

    void Gui::setupBasicEnnemies()
    {
        _r->add_system(ecs::systems::EnnemiesMilespatesSystem());
        _r->add_system(ecs::systems::BasicRandomEnnemiesSystem());
    }

    void Gui::setupBackground()
    {
        _factory.createEntity("config/background/background.json");
        _factory.createEntity("config/background/background_2.json");
        _factory.createEntity("config/background/background_3.json");
        _factory.createEntity("config/background/background_4.json");

        ecs::systems::ParalaxSystem parallaxSystem;
        _r->add_system(parallaxSystem);
    }

    void Gui::setupGame()
    {
        _factory = ecs::ComponentFactory(_r, ecs::ComponentFactory::Mode::Client);
        setupBackground();
        setupPlayer();
        setupWeapon();
        setupBasicEnnemies();
        setupCollisons();
        setupDestroy();
    }

    int Gui::run()
    {
        setupGame();
        auto &drawables = _r->get_components<ecs::component::Drawable>();
        auto &sprites = _r->get_components<ecs::component::Sprite>();
        auto &positions = _r->register_component<ecs::component::Position>();
        auto &animations = _r->register_component<ecs::component::Animations>();
        auto &size = _r->register_component<ecs::component::Size>();

        while (_window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
            }

            if (_systemClock.getSeconds() > FRAME_PER_SECONDS(2)) {
                _r->run_systems();
                _systemClock.restart();
            }

            if (_drawClock.getSeconds() > FRAME_PER_SECONDS(60)) {
                _window.clear();
                for (auto &&[draws, anim, spri, si, pos] :
                     ecs::custom_zip(drawables, animations, sprites, size, positions)) {
                    if (!draws || !anim || !spri || !si || !pos) {
                        continue;
                    }
                    if (spri->_pathToSprite.empty()) {
                        continue;
                    }
                    sf::Sprite sprite;
                    sprite.setPosition(pos->_x, pos->_y);
                    sprite.setScale(si->_width, si->_height);
                    sprite.setTextureRect(sf::IntRect(
                        anim->_x,
                        anim->_y,
                        anim->_width,
                        anim->_height));
                    sprite.setTexture(_textureManager.getTexture(spri->_pathToSprite));
                    _window.draw(sprite);
                }
                _drawClock.restart();
            }
            _window.display();
        }
        _window.clear();
        _r->run_systems();
        return SUCCESS;
    }

} // namespace rtype
