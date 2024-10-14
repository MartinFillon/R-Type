/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** menu file
*/

#include "Menu.hpp"

namespace rtype::client {
    Menu::Menu(sf::RenderWindow &window) : _win(window), _isMenuOpen(true)
    {
        setupMenu();
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
    }

    void Menu::setupBackground()
    {
        _backgroundTexture.loadFromFile(BG_PATH);
        _backgroundTexture.setRepeated(true);
        _backgroundSprite.setTexture(_backgroundTexture);
        _backgroundSprite.setPosition(BG_POS_X, BG_POS_Y);
        _bgScaleX = static_cast<float>(_win.getSize().x) / _backgroundTexture.getSize().x;
        _bgScaleY = static_cast<float>(_win.getSize().y) / _backgroundTexture.getSize().y;
        _backgroundSprite.setScale(_bgScaleX, _bgScaleY);
    }

    void Menu::setupMenuFont()
    {
        _fontTitle.loadFromFile(TITLE_FONT);
        _fontText.loadFromFile(TEXT_FONT);
    }

    void Menu::setupMenuInputRect()
    {
        _ipRect = sf::RectangleShape(sf::Vector2f(RECT_SIZE_Y, RECT_SIZE_X));
        _ipRect.setFillColor(sf::Color::White);
        _ipRect.setPosition(LEFT_MARGE, IP_RECT_POS_X);
    }

    void Menu::setupPlayButton()
    {
        _menutitle[0].setString(BUTTON_PLAY);
        _menutitle[0].setFont(_fontTitle);
        _menutitle[0].setPosition(LEFT_MARGE, PLAY_POS_X);
    }

    void Menu::setupOptionsButton()
    {
        _menutitle[1].setString(BUTTON_OPTIONS);
        _menutitle[1].setFont(_fontTitle);
        _menutitle[1].setPosition(LEFT_MARGE, OPTIONS_POS_X);
    }

    void Menu::setupQuitButton()
    {
        _menutitle[2].setString(BUTTON_QUIT);
        _menutitle[2].setFont(_fontTitle);
        _menutitle[2].setPosition(LEFT_MARGE, QUIT_POS_X);
    }

    void Menu::setupMenuTitle()
    {
        _menutitle[3].setString(MENU_TITLE);
        _menutitle[3].setFont(_fontTitle);
        _menutitle[3].setPosition(TITLE_POS_Y, TITLE_POS_X);
        _menutitle[3].setCharacterSize(FONT_SIZE_TITLE);
    }

    void Menu::setupIpButton()

    {
        _menutitle[4].setString(BUTTON_IP);
        _menutitle[4].setFont(_fontText);
        _menutitle[4].setPosition(LEFT_MARGE, IP_POS_X);
        _menutitle[4].setCharacterSize(FONT_SIZE_IP);
    }

    void Menu::setupRenderFont()
    {
        _menuDisplayInput.setFont(_fontText);
        _menuDisplayInput.setPosition(LEFT_MARGE, TEXT_POS_X);
        _menuDisplayInput.setCharacterSize(FONT_SIZE_INPUT);
        _menuDisplayInput.setFillColor(sf::Color::Black);
    }

    void Menu::menuCloseWindow(sf::Event &event)
    {
        if (event.type == sf::Event::Closed) {
            _win.close();
            _isMenuOpen = false;
        }
    }

    std::string Menu::menuButtonPressed()
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_win);

        for (int i = 0; i < 3; i++) {
            if (_menutitle[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                switch (i) {
                    case 0:
                        _isMenuOpen = false;
                        if (_menuClientInput.empty()) {
                            return EMPTY_ADRESS;
                        } else
                            return _menuClientInput;
                    case 1:
                        break;
                    case 2:
                        _isMenuOpen = false;
                        return _menuClientInput;
                }
            }
        }
        if (_ipRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            _isWritting = true;
            _ipRect.setOutlineThickness(BORDER_RECT_PRESS);
            _ipRect.setOutlineColor(sf::Color::Blue);
        } else {
            _isWritting = false;
            _ipRect.setOutlineThickness(0);
        }
        return "";
    }

    void Menu::menuEnterToPlay()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !_menuClientInput.empty()) {
            _isMenuOpen = false;
        }
    }

    void Menu::menuTextEntered(sf::Event &event)
    {
        if (event.text.unicode < ASCII_LIM) {
            _inputChar = static_cast<char>(event.text.unicode);
            if (_inputChar == DEL_BUTTON && !_menuClientInput.empty()) {
                _menuClientInput.pop_back();
            } else if (_inputChar > NON_ASCII_CHAR && _inputChar < ASCII_LIM) {
                _menuClientInput += _inputChar;
            }
            _menuDisplayInput.setString(_menuClientInput);
        }
    }

    void Menu::menuShaderParams(sf::Shader &para)
    {
        _bgOffset += _menuClock.restart().asSeconds() / PARA_SPEED;
        para.setUniform(OFFSET, _bgOffset);
    }

    void Menu::menuDrawtitles()
    {
        for (int i = 0; i < NB_TITLES; i++) {
            _win.draw(_menutitle[i]);
        }
    }

    void Menu::menuDraw(sf::Shader &para)
    {
        _win.clear();
        _win.draw(_backgroundSprite, &para);
        menuDrawtitles();
        _win.draw(_ipRect);
        _win.draw(_menuDisplayInput);
        _win.display();
    }

    int Menu::menuLoadShader()
    {
       if (!_para.loadFromMemory(
                "uniform float offset;"
                "void main() {"
                "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
                "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
                "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;"
                "    gl_FrontColor = gl_Color;"
                "}",
                sf::Shader::Vertex
            )) {
                return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    std::string Menu::launchMenu()
    {
        menuLoadShader();

        while (_isMenuOpen && _win.isOpen()) {
            sf::Event event;
            while (_win.pollEvent(event) && _isMenuOpen) {
                menuCloseWindow(event);

                if (event.type == sf::Event::MouseButtonPressed) {
                    _menuClientInput = menuButtonPressed();
                }
                if (_isWritting && event.type == sf::Event::TextEntered) {
                    menuTextEntered(event);
                }

                menuEnterToPlay();
            }

            menuShaderParams(_para);
            menuDraw(_para);
        }
        return _menuClientInput;
    }
} // namespace rtype::client
