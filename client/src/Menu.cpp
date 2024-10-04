/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** menu file
*/

#include "Menu.hpp"

rtype::Menu::Menu(sf::RenderWindow &window) : _win(window), _isMenuOpen(true) {}

void rtype::Menu::setupMenu()
{
    _backgroundTexture.loadFromFile(BG_PATH);
    _backgroundTexture.setRepeated(true);
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setPosition(0, 0);
    _bgScaleX = static_cast<float>(_win.getSize().x) / _backgroundTexture.getSize().x;
    _bgScaleY = static_cast<float>(_win.getSize().y) / _backgroundTexture.getSize().y;
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

std::string rtype::Menu::launchMenu()
{
    sf::Shader parallaxShader;
    if (!parallaxShader.loadFromMemory(
            "uniform float offset;"
            "void main() {"
            "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
            "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
            "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;"
            "    gl_FrontColor = gl_Color;"
            "}",
            sf::Shader::Vertex
        )) {
        return "";
    }
    while (_isMenuOpen && _win.isOpen()) {
        sf::Event event;
        while (_win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _win.close();
                _isQuitPress = true;
                break;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_win);
                for (int i = 0; i < 3; i++) {
                    if (_menutitle[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        switch (i) {
                            case 0:
                                _isMenuOpen = false;
                                return _menuClientInput;
                            case 1:
                                break;
                            case 2:
                                _win.close();
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
                _isMenuOpen = false;
                break;
            }
        }

        _bgOffset += _menuClock.restart().asSeconds() / PARA_SPEED;
        parallaxShader.setUniform(OFFSET, _bgOffset);
        _win.clear();
        _win.draw(_backgroundSprite, &parallaxShader);

        for (int i = 0; i < 5; i++) {
            _win.draw(_menutitle[i]);
        }

        _win.draw(_ipRect);
        _win.draw(_menuDisplayInput);
        _win.display();
    }

    return "";
}
