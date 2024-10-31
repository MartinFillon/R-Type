/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** menu file
*/

#include "Menu.hpp"
#include <unistd.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "LobbyMenu.hpp"

namespace rtype::client {
    Menu::Menu(sf::RenderWindow &window) : _win(window), _isMenuOpen(true)
    {

    }

    void Menu::setupMenu()
    {
        setupBackground();
        setupMenuFont();
        setupMenuInputRect();
        setupPlayButton();
        setupOptionsButton();
        setupQuitButton();
        setupMenuTitle();
        setupIpButton();
        setupRenderFont();
        setupMenuMusic();
    }

    void Menu::setupBackground()
    {
        (void)_backgroundTexture.loadFromFile(BG_PATH);
        _backgroundTexture.setRepeated(true);
        _bgScaleX = static_cast<float>(_win.getSize().x) / _backgroundTexture.getSize().x;
        _bgScaleY = static_cast<float>(_win.getSize().y) / _backgroundTexture.getSize().y;
        //_backgroundSprite.setScale(_bgScaleX, _bgScaleY);

        (void)_para.loadFromMemory(
            "uniform float offset;"
            "void main() {"
            "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
            "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
            "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;"
            "    gl_FrontColor = gl_Color;"
            "}",
            sf::Shader::Type::Vertex
        );
    }

    void Menu::setupMenuFont()
    {
        (void)_fontTitle.openFromFile(TITLE_FONT);
        (void)_fontText.openFromFile(TEXT_FONT);
    }

    void Menu::setupMenuInputRect()
    {
        _ipRect = sf::RectangleShape(sf::Vector2f(RECT_SIZE_Y, RECT_SIZE_X));
        _ipRect.setFillColor(sf::Color::White);
        _ipRect.setPosition({LEFT_MARGE, IP_RECT_POS_X});
    }

    sf::Text Menu::setupPlayButton()
    {
        sf::Text playButton(_fontTitle, BUTTON_PLAY);
        playButton.setPosition({LEFT_MARGE, PLAY_POS_X});

        return playButton;
    }

    sf::Text Menu::setupOptionsButton()
    {
        sf::Text optionsButton(_fontTitle, BUTTON_OPTIONS);
        optionsButton.setPosition({LEFT_MARGE, OPTIONS_POS_X});

        return optionsButton;
    }

    sf::Text Menu::setupQuitButton()
    {
        sf::Text quitButton(_fontTitle, BUTTON_QUIT);
        quitButton.setPosition({LEFT_MARGE, QUIT_POS_X});

        return quitButton;
    }

    sf::Text Menu::setupMenuTitle()
    {
        sf::Text menuTitle(_fontTitle, MENU_TITLE, FONT_SIZE_TITLE);

        menuTitle.setPosition({TITLE_POS_Y, TITLE_POS_X});

        return menuTitle;
    }

    sf::Text Menu::setupIpButton()

    {
        sf::Text ipButton(_fontText, BUTTON_IP, FONT_SIZE_IP);

        ipButton.setPosition({LEFT_MARGE, IP_POS_X});
        return ipButton;
    }

    sf::Text Menu::setupRenderFont()
    {
        auto _menuDisplayInput = sf::Text(_fontText, _menuClientInput, FONT_SIZE_INPUT);
        _menuDisplayInput.setPosition({LEFT_MARGE, TEXT_POS_X});
        _menuDisplayInput.setFillColor(sf::Color::Black);

        return _menuDisplayInput;
    }

    void Menu::setupMenuMusic()
    {
        (void)_bufferMenuMusic.loadFromFile(MENU_MUSIC);
        _menuMusic.setBuffer(_bufferMenuMusic);
        _menuMusic.setLooping(true);
    }

    std::string Menu::menuButtonPressed()
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_win);
        sf::Text _menutitle[5] = {
            setupPlayButton(), setupOptionsButton(), setupQuitButton(), setupIpButton(), setupMenuTitle()
        };

        for (int i = 0; i < NB_TITLES; i++) {
            if (_menutitle[i].getGlobalBounds().contains(
                    {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)}
                )) {
                switch (i) {
                    case CASE_PLAY:
                        _isMenuOpen = false;
                        if (_menuClientInput.empty()) {
                            return EMPTY_ADRESS;
                        } else
                            return _menuClientInput;
                    case CASE_OPTIONS:
                        break;
                    case CASE_QUIT:
                        _isMenuOpen = false;
                        return _menuClientInput;
                }
            }
        }
        if (_ipRect.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
            _isWritting = true;
            _ipRect.setOutlineThickness(BORDER_RECT_PRESS);
            _ipRect.setOutlineColor(sf::Color::Blue);
        } else {
            _isWritting = false;
            _ipRect.setOutlineThickness(BORDER_RECT_NO_PRESS);
        }
        return "";
    }

    void Menu::menuEnterToPlay()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && !_menuClientInput.empty()) {
            _isMenuOpen = false;
        }
    }

    void Menu::menuTextEntered(sf::Event::TextEntered const *event)
    {
        if (event->unicode < ASCII_LIM) {
            _inputChar = static_cast<char>(event->unicode);
            if (_inputChar == DEL_BUTTON && !_menuClientInput.empty()) {
                _menuClientInput.pop_back();
            } else if (_inputChar > NON_ASCII_CHAR && _inputChar < ASCII_LIM) {
                _menuClientInput += _inputChar;
            }
        }
    }

    void Menu::menuShaderParams()
    {
        _bgOffset += _menuClock.restart().asSeconds() / PARA_SPEED;
        _para.setUniform(OFFSET, _bgOffset);
    }

    void Menu::menuDrawtitles()
    {
        sf::Text _menutitle[5] = {
            setupPlayButton(), setupOptionsButton(), setupQuitButton(), setupIpButton(), setupMenuTitle()
        };

        for (int i = 0; i < NB_TITLES; i++) {
            _win.draw(_menutitle[i]);
        }
    }

    void Menu::menuDraw()
    {
        sf::Sprite _backgroundSprite(_backgroundTexture);
        auto _menuDisplayInput = setupRenderFont();

        _backgroundSprite.setPosition({BG_POS_X, BG_POS_Y});
        _backgroundSprite.setScale({_bgScaleX, _bgScaleY});
        _win.clear();
        _win.draw(_backgroundSprite, &_para);
        menuDrawtitles();
        _win.draw(_ipRect);
        _win.draw(_menuDisplayInput);
        _win.display();
    }

    void Menu::launchMusic()
    {
        if (_menuMusic.getStatus() != sf::SoundSource::Status::Playing) {
            _menuMusic.play();
        }
    }

    /*std::string Menu::launchMenu()
    {
        setupMenuMusic();

        while (_isMenuOpen && _win.isOpen()) {
            while (const std::optional event = _win.pollEvent()) {

                launchMusic();
                if (event->is<sf::Event::Closed>()) {
                    _isMenuOpen = false;
                    break;
                }

                if (event->is<sf::Event::MouseButtonPressed>()) {
                    _menuClientInput = menuButtonPressed();
                }
                const auto *t = event->getIf<sf::Event::TextEntered>();
                if (_isWritting && t) {
                    menuTextEntered(t);
                }

                menuEnterToPlay();
            }
    }*/

    std::string Menu::launchMenu()
    {
        setupMenu();

        while (_isMenuOpen && _win.isOpen()) {
            menuShaderParams();
            menuDraw();
            while (const std::optional event = _win.pollEvent()) {
                launchMusic();
                if (event->is<sf::Event::Closed>()) {
                    _isMenuOpen = false;
                    break;
                }

                if (event->is<sf::Event::MouseButtonPressed>()) {
                    _menuClientInput = menuButtonPressed();
                }
                const auto *t = event->getIf<sf::Event::TextEntered>();
                if (_isWritting && t) {
                    menuTextEntered(t);
                }

                menuEnterToPlay();
            }        }
        _menuMusic.stop();
        return _menuClientInput;
    }
} // namespace rtype::client
