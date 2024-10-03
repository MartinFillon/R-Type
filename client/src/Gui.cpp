/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#include "Gui.hpp"
#include <iostream>

#include "Clock.hpp"
#include "ComponentFactory.hpp"
#include "ImageResolver.hpp"
#include "Systems/BasicRandomEnnemiesSystem.hpp"
#include "Systems/CollisionsSystem.hpp"
#include "Systems/GunFireSystem.hpp"
#include "Systems/ParallaxSystem.hpp"
#include "Systems/PlayerMouvementSystem.hpp"
#include "ZipperIterator.hpp"

namespace rtype {
    Gui::Gui()
        : ecs::IContext(), _window(sf::VideoMode(1920, 1080), GAME_NAME), _r(std::make_shared<ecs::Registry>()),
          _drawClock(ecs::Clock()), _systemClock(ecs::Clock()), _isQuitPress(false), _menuClientInput("")
    {
        setupMenu();
    }

    Gui::~Gui() {}

    sf::RenderWindow &Gui::getRenderWindow()
    {
        return _window;
    }

    void Gui::setupCollisons()
    {
        ecs::systems::CollisionsSystem collisions;
        _r->add_system(collisions);
    }

    void Gui::setupWeapon()
    {
        ecs::systems::GunFireSystem gunSystem;
        _r->add_system(gunSystem);
    }

    void Gui::setupBasicEnnemies()
    {
        ecs::systems::BasicRandomEnnemiesSystem basicEnnemies;
        _r->add_system(basicEnnemies);
    }

    void Gui::setupPlayer()
    {
        _factory.createEntity("config/player.json");

        std::cout << "Player created" << std::endl;

        ecs::systems::PlayerMouvementSystem playerMovementSystem;
        _r->add_system(playerMovementSystem);
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
    }

    void Gui::setupMenu()
    {
        _fontTitle.loadFromFile("assets/fonts/ARCADE_I.ttf");
        _fontText.loadFromFile("assets/fonts/OpenSans-Semibold.ttf");

        _menuText[0].setFont(_fontTitle);
        _menuText[0].setString("Play");
        _menuText[0].setPosition(800, 300);
        _menuText[1].setFont(_fontTitle);
        _menuText[1].setString("Options");
        _menuText[1].setPosition(800, 400);
        _menuText[2].setFont(_fontTitle);
        _menuText[2].setString("Quit");
        _menuText[2].setPosition(800, 500);
        _menuDisplayInput.setFont(_fontText);
        _menuDisplayInput.setPosition(800, 600);
        _menuDisplayInput.setCharacterSize(15);
        _menuDisplayInput.setFillColor(sf::Color::White);
    }

    void Gui::launchMenu()
    {
        while (_isMenuOpen && _window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                    _isQuitPress = true;
                    break;
                }
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        _inputChar = static_cast<char>(event.text.unicode);
                        if (_inputChar == 8 && !_menuClientInput.empty()) {
                            _menuClientInput.pop_back();
                        } else if (_inputChar > 31 && _inputChar < 127) {
                            _menuClientInput += _inputChar;
                        }
                        _menuDisplayInput.setString(_menuClientInput);
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                    for (int i = 0; i < 3; i++) {
                        if (_menuText[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            switch (i) {
                                case 0:
                                    _isMenuOpen = false;
                                    setupGame();
                                    break;
                                case 1:
                                    break;
                                case 2:
                                    _window.close();
                                    _isQuitPress = true;
                                    break;
                            }
                        }
                    }
                }
            }
            _window.clear();
            _r->run_systems();
            for (int i = 0; i < 3; i++) {
                _window.draw(_menuText[i]);
            }
            _window.draw(_menuDisplayInput);
            _window.display();
        }
    }

    int Gui::run()
    {
        launchMenu();

        if (_isQuitPress) { return EXIT_SUCCESS; }

        auto &drawables = _r->get_components<ecs::component::Drawable>();
        auto &sprites = _r->get_components<ecs::component::Sprite>();
        auto &positions = _r->register_component<ecs::component::Position>();
        auto &animations = _r->register_component<ecs::component::Animations>();
        auto &size = _r->register_component<ecs::component::Size>();
        int testTick(20);

        while (_window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
            }

            if (_systemClock.getSeconds() > (1 / 5)) {
                _r->run_systems();
                _systemClock.restart();
            }

            if (_drawClock.getSeconds() > (1 / 60)) {
                _window.clear();
                for (auto &&[draws, anim, spri, si, pos] :
                     ecs::custom_zip(drawables, animations, sprites, size, positions)) {
                    if (!draws || !anim || !spri || !si || !pos) {
                        continue;
                    }
                    sf::Texture texture;
                    ecs::ImageResolver image(PATH_TO_ASSETS);
                    std::string pathToImage = image.getImage(spri->_pathToSprite);
                    if (pathToImage.empty()) {
                        continue;
                    }
                    texture.loadFromMemory(
                        pathToImage.c_str(),
                        pathToImage.size(),
                        sf::IntRect(anim->_x, anim->_y, anim->_width, anim->_height)
                    );
                    sf::Sprite sprite;
                    sprite.setPosition(pos->_x, pos->_y);
                    sprite.setScale(si->_width, si->_height);
                    sprite.setTexture(texture);
                    _window.draw(sprite);
                }
                _drawClock.restart();
            }
            _window.display();
        }
        return EXIT_SUCCESS;
    }

} // namespace rtype
