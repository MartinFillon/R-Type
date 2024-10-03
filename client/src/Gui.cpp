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
        : ecs::IContext(), _window(sf::VideoMode(1920, 1080), GAME_NAME),
        _r(std::make_shared<ecs::Registry>()), _drawClock(ecs::Clock()), _bgOffset(0.0),
        _systemClock(ecs::Clock()), _isQuitPress(false), _isWritting(false), _isMenuOpen(true)
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
        _backgroundTexture.loadFromFile(BG_PATH);
        _backgroundTexture.setRepeated(true);
        _backgroundSprite.setTexture(_backgroundTexture);
        _backgroundSprite.setPosition(0, 0);
        _bgScaleX = static_cast<float>(_window.getSize().x) / _backgroundTexture.getSize().x;
        _bgScaleY = static_cast<float>(_window.getSize().y) / _backgroundTexture.getSize().y;
        _backgroundSprite.setScale(_bgScaleX, _bgScaleY);

        _fontTitle.loadFromFile(TITLE_FONT);
        _fontText.loadFromFile(TEXT_FONT);

        _ipRect = sf::RectangleShape(sf::Vector2f(RECT_SIZE_Y, RECT_SIZE_X));
        _ipRect.setFillColor(sf::Color::White);
        _ipRect.setPosition(LEFT_MARGE, IP_RECT_POS_X);

        _menutitle[0].setString(BUTTON_PLAY);
        _menutitle[0].setFont(_fontTitle);
        _menutitle[0].setPosition(LEFT_MARGE, PLAY_POS_X);

        _menutitle[1].setString(BUTTON_IP);
        _menutitle[1].setFont(_fontText);
        _menutitle[1].setPosition(LEFT_MARGE, IP_POS_X);
        _menutitle[1].setCharacterSize(FONT_SIZE_IP);

        _menutitle[2].setString(BUTTON_OPTIONS);
        _menutitle[2].setFont(_fontTitle);
        _menutitle[2].setPosition(LEFT_MARGE, OPTIONS_POS_X);

        _menutitle[3].setString(MENU_TITLE);
        _menutitle[3].setFont(_fontTitle);
        _menutitle[3].setPosition(TITLE_POS_Y, TITLE_POS_X);
        _menutitle[3].setCharacterSize(FONT_SIZE_TITLE);

        _menutitle[4].setString(BUTTON_QUIT);
        _menutitle[4].setFont(_fontTitle);
        _menutitle[4].setPosition(LEFT_MARGE, QUIT_POS_X);

        _menuDisplayInput.setFont(_fontText);
        _menuDisplayInput.setPosition(LEFT_MARGE, TEXT_POS_X);
        _menuDisplayInput.setCharacterSize(FONT_SIZE_INPUT);
        _menuDisplayInput.setFillColor(sf::Color::Black);
    }

    void Gui::launchMenu()
    {
        sf::Shader parallaxShader;
        if (!parallaxShader.loadFromMemory(
            "uniform float offset;"

            "void main() {"
            "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
            "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
            "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;"
            "    gl_FrontColor = gl_Color;"
            "}", sf::Shader::Vertex)) {
            return;
        }
        sf::Clock clock;

        while (_isMenuOpen && _window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                    _isQuitPress = true;
                    break;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                    for (int i = 0; i < 3; i++) {
                        if (_menutitle[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
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
                    if (_ipRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        _isWritting = true;
                        _ipRect.setOutlineThickness(3.5);
                        _ipRect.setOutlineColor(sf::Color::Blue);
                    } else {
                        _isWritting = false;
                        _ipRect.setOutlineThickness(0);
                    }
                }

                if (_isWritting && event.type == sf::Event::TextEntered) {
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !_menuClientInput.empty()) {
                    setupGame();
                    _isMenuOpen = false;
                    break;
                }
            }

            _bgOffset += clock.restart().asSeconds() / PARA_SPEED;
            parallaxShader.setUniform(OFFSET, _bgOffset);
            _window.clear();
            _window.draw(_backgroundSprite, &parallaxShader);

            for (int i = 0; i < 5; i++) {
                _window.draw(_menutitle[i]);
            }

            _window.draw(_ipRect);
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
