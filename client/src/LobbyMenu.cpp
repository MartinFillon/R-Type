/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** LOBBY
*/

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "LobbyMenu.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "Menu.hpp"
#include "TCPCommunication.hpp"

rtype::client::LobbyMenu::LobbyMenu(sf::RenderWindow &window): _running(true), _window(window), _ready(false), _loading(true), _createActivate(false)
{

}

int rtype::client::LobbyMenu::launchLobby(std::shared_ptr<TCPCommunication> server)
{
    _server = std::move(server);
    setup();

    while (_running && _window.isOpen() && !_server->getPort()) {
        if (!_running) {
            return _port;
        }
        update();
        display();
        event();
    }
    setupLoadingGame();

    while (_running && _window.isOpen() && _loading) {
        loadingGame();
    }

    if (_server->getPort()) {
        return _server->getPort();
    }

    return _port;
}

void rtype::client::LobbyMenu::setup()
{
    setupBackground();
}

void rtype::client::LobbyMenu::setupLoadingGame()
{
    _loadingRectangle.setFillColor(sf::Color::Black);
    _loadingRectangle.setOutlineColor(sf::Color::White);
    _loadingRectangle.setOutlineThickness(RECT_THICKNESS);
    _loadingRectangle.setSize({LOADING_RECT_SIZE_X, LOADING_RECT_SIZE_Y});
    _loadingRectangle.setPosition({LOADING_RECT_POS_X, LOADING_RECT_POS_Y});

    _loadingPourcent.setFillColor(sf::Color::Green);
    _loadingPourcent.setSize({PERCENT_RECT_SIZE_X, PERCENT_RECT_SIZE_Y});
    _loadingPourcent.setPosition({PERCENT_RECT_POS_X, PERCENT_RECT_POS_Y});

    _loadingText.setPosition({LOADING_TEXT_POS_X, LOADING_TEXT_POS_Y});
    _loadingText.setString(LOADING_TITLE(std::to_string(_loadingValue)));
    _loadingText.setFillColor(sf::Color::White);
    _loadingText.setCharacterSize(TEXT_SIZE);

    _loadingStop = STOP_START_VALIUE;
}

void rtype::client::LobbyMenu::loadingGame()
{
    _window.clear();
    updateBackground();

    if (_loadingValue >= MAX_LOADING_VALUE) {
        _loading = false;
        return;
    }

    if (_loadingValue >= FUN_STOP && _loadingStop) {
        _loadingStop++;
        if (_loadingStop == LOADING_STOP) {
            _loadingStop = RESET_STOP;
        }
    }

    if (_loadingStop == TIME_STOP or !_loadingStop) {
        _loadingValue += LOADING_LOAD_VALUE;
    }

    sf::Font font;

    _window.draw(_backgroundSprite, &_shader);

    font.loadFromFile(FONT_PATH);
    _loadingText.setFont(font);

    _loadingPourcent.setSize({_loadingValue * PERCENT_SIZE_ADAPT, PERCENT_RECT_SIZE_Y});
    _loadingText.setString(LOADING_TITLE(std::to_string((int)_loadingValue)));

    _window.draw(_loadingRectangle);
    _window.draw(_loadingPourcent);
    _window.draw(_loadingText);

    _window.display();
}

void rtype::client::LobbyMenu::setupBackground()
{
    _backgroundTexture.loadFromFile(BG_PATH);
    _backgroundTexture.setRepeated(true);
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setPosition(BG_POS_X, BG_POS_Y);
    _bgScaleX = static_cast<float>(_window.getSize().x) / _backgroundTexture.getSize().x;
    _bgScaleY = static_cast<float>(_window.getSize().y) / _backgroundTexture.getSize().y;
    _backgroundSprite.setScale(_bgScaleX, _bgScaleY);

    _shader.loadFromMemory(
        "uniform float offset;"
        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;"
        "    gl_FrontColor = gl_Color;"
        "}",
        sf::Shader::Vertex
    );
}

void rtype::client::LobbyMenu::createNewLobby(sf::Event &event)
{
    char _inputChar;

    if (event.text.unicode < ASCII_LIM) {
        _inputChar = static_cast<char>(event.text.unicode);
        if (_inputChar == DEL_BUTTON && !_newLobbyName.empty()) {
            _newLobbyName.pop_back();
        } else if (_inputChar > NON_ASCII_CHAR && _inputChar < ASCII_LIM) {
            _newLobbyName += _inputChar;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !_newLobbyName.empty()) {
        _server.get()->send(CREATE_CMD(_newLobbyName));
        _server.get()->read();
        _newLobbyName.clear();
    }
}

void rtype::client::LobbyMenu::event()
{
    sf::Event event;

    while (_window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            _running = false;
            _window.close();
            return;
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mouse = sf::Mouse::getPosition(_window);

            if (_lobbyCreate.getGlobalBounds().contains(mouse.x, mouse.y)) {
                _createActivate = true;
            } else {
                _createActivate = false;
            }

            for (int i = 0; i < _lobbies.size(); i++) {
                if (!_lobby.empty() && _lobbies[i].join.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    _server.get()->send(QUIT_CMD(_lobbies[i].name));
                    if (_server.get()->read().find("200") != std::string::npos) {
                        _lobby.clear();
                        _ready = false;
                    }
                    continue;
                }

                if (!_lobbies[i].running && _lobby.empty() && _lobbies[i].join.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    _server.get()->send(JOIN_CMD(_lobbies[i].name));
                    if (_server.get()->read().find("200") != std::string::npos) {
                        _lobby = _lobbies[i].name;
                        _ready = false;
                    }
                    continue;
                }

                if (!_lobby.empty() && _lobbies[i].buttonReady.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    if (!_ready) {
                        _server.get()->send(READY_CMD);
                        if (_server.get()->read().find("200") != std::string::npos) {
                            _ready = true;
                        }
                        continue;
                    }

                    if (_ready) {
                        _server.get()->send(UNREADY_CMD);
                        if (_server.get()->read().find("200") != std::string::npos) {
                            _ready = false;
                        }
                        continue;
                    }
                }

                if (_lobbies[i].name == _lobby && _lobbies[i].nbPlayers == _lobbies[i].ready && _lobbies[i].nbPlayers && _lobbies[i].start.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    _server.get()->send(START_CMD);
                    std::string response = _server.get()->read();
                    if (response.find(NETWORK_METHOD_GAME) != std::string::npos) {
                        _running = false;
                        _port = std::stoi(response.substr(response.find(TOKEN_PARSE_NETWORK) + 1));
                    }
                    return;
                }
            }

        }
        if (_createActivate && event.type == sf::Event::TextEntered && _lobby.empty()) {
            createNewLobby(event);
        }
    }
}

void rtype::client::LobbyMenu::update()
{
    updateBackground();
    updateLobbies();
}

void rtype::client::LobbyMenu::updateLobbies()
{
    _server.get()->send(LIST_CMD);

    std::string lobby = _server.get()->read();

    _lobbies.clear();

    while (lobby.find("200") == std::string::npos && lobby.find(NETWORK_METHOD_GAME) == std::string::npos) {

        std::string name = lobby.substr(0, lobby.find(TOKEN_PARSE_NETWORK));
        std::string running = lobby.substr(lobby.find(TOKEN_PARSE_NETWORK) + 1, 1);
        std::string nbPlayers = lobby.substr(lobby.find(TOKEN_PARSE_NETWORK) + 3, 1);
        std::string ready = lobby.substr(lobby.find(TOKEN_PARSE_NETWORK) + 5, 1);

        struct Lobby newLobby = { name, std::stoi(nbPlayers), std::stoi(running), std::stoi(ready), sf::RectangleShape(), sf::RectangleShape(), sf::RectangleShape(), sf::RectangleShape()};

        _lobbies.push_back(newLobby);

        lobby.clear();
        lobby = _server.get()->read();
    }
}

void rtype::client::LobbyMenu::updateBackground()
{
    _bgOffset += _backgroundClock.restart().asSeconds() / PARALAX_SPEED;
    _shader.setUniform(OFFSET, _bgOffset);
}

void rtype::client::LobbyMenu::display()
{
    _window.clear();
    _window.draw(_backgroundSprite, &_shader);
    displayLobbies();
    _window.display();
}

void rtype::client::LobbyMenu::displayLobbies()
{
    int i = 0;

    for (i = 0; i < _lobbies.size(); i++) {

        _lobbies[i].rectangle.setFillColor(sf::Color::Black);
        _lobbies[i].rectangle.setOutlineColor(sf::Color::White);
        _lobbies[i].rectangle.setOutlineThickness(RECT_THICKNESS);
        _lobbies[i].rectangle.setSize({LOBBY_RECT_SIZE_X, LOBBY_RECT_SIZE_Y});
        _lobbies[i].rectangle.setPosition({LOBBY_RECT_POS_X, LOBBY_RECT_POS_Y(float(i))});

        _lobbies[i].start.setFillColor(sf::Color::Black);
        _lobbies[i].start.setOutlineColor(sf::Color::Green);
        _lobbies[i].start.setOutlineThickness(RECT_THICKNESS);
        _lobbies[i].start.setSize({START_BUTTON_SIZE_X, START_BUTTON_SIZE_Y});
        _lobbies[i].start.setPosition({START_BUTTON_POS_X, START_BUTTON_POS_Y((float)i)});

        _lobbies[i].join.setFillColor(sf::Color::Black);
        _lobbies[i].join.setOutlineColor(_lobby.empty() ? sf::Color::Green : sf::Color::Red);
        _lobbies[i].join.setOutlineThickness(RECT_THICKNESS);
        _lobbies[i].join.setSize({JOIN_BUTTON_SIZE_X, JOIN_BUTTON_SIZE_Y});
        _lobbies[i].join.setPosition({JOIN_BUTTON_POS_X, JOIN_BUTTON_POS_Y(float(i))});

        _lobbies[i].buttonReady.setFillColor(sf::Color::Black);
        _lobbies[i].buttonReady.setOutlineColor(_ready ? sf::Color::Green : sf::Color::Red);
        _lobbies[i].buttonReady.setOutlineThickness(RECT_THICKNESS);
        _lobbies[i].buttonReady.setSize({READY_BUTTON_SIZE_X, READY_BUTTON_SIZE_Y});
        _lobbies[i].buttonReady.setPosition({READY_BUTTON_POS_X, READY_BUTTON_POS_Y(float(i))});

        sf::Text text;

        text.setPosition({LOBBY_NAME_POS_X, LOBBY_NAME_POS_Y((float)i)});
        text.setString(_lobbies[i].name);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(TEXT_SIZE);

        sf::Text textStart;

        textStart.setPosition({TEXT_START_POS_X, TEXT_START_POS_y((float)i)});
        textStart.setString(START_TITLE);
        textStart.setFillColor(sf::Color::Green);
        textStart.setCharacterSize(TEXT_SIZE);

        sf::Text textJoin;

        textJoin.setPosition({TEXT_JOIN_POS_X((float)!_lobby.empty()), TEXT_JOIN_POS_Y(float(i))});
        textJoin.setString(_lobby.empty() ? JOIN_TITLE : QUIT_TITLE);
        textJoin.setFillColor(_lobby.empty() ? sf::Color::Green: sf::Color::Red);
        textJoin.setCharacterSize(TEXT_SIZE);

        sf::Text textReady;

        textReady.setPosition({TEXT_READY_POS_X, TEXT_READY_POS_Y(float(i))});
        textReady.setString(READY_TITLE);
        textReady.setFillColor(_ready ? sf::Color::Green: sf::Color::Red);
        textReady.setCharacterSize(TEXT_SIZE);

        sf::Text nbPlayers;

        nbPlayers.setPosition({TEXT_NB_P_POS_X, TEXT_JOIN_POS_Y(float(i))});
        nbPlayers.setString(std::to_string(_lobbies[i].nbPlayers) + LOBBY_MAX_PLAYERS);
        nbPlayers.setFillColor(_lobbies[i].nbPlayers == _lobbies[i].ready && _lobbies[i].nbPlayers ? sf::Color::Green : sf::Color::White);
        nbPlayers.setCharacterSize(TEXT_SIZE);

        sf::Font font;

        font.loadFromFile(FONT_PATH);
        text.setFont(font);
        nbPlayers.setFont(font);
        textJoin.setFont(font);
        textReady.setFont(font);
        textStart.setFont(font);

        _window.draw(_lobbies[i].rectangle);
        _window.draw(text);
        _window.draw(nbPlayers);

        if (!_lobbies[i].running && _lobby.empty() && _lobbies[i].nbPlayers != MAX_LOBBIES && _lobbies[i].running == false) {
            _window.draw(_lobbies[i].join);
            _window.draw(textJoin);
        }

        if (!_lobbies[i].running && _lobby == _lobbies[i].name) {
            _window.draw(_lobbies[i].join);
            _window.draw(textJoin);
            _window.draw(_lobbies[i].buttonReady);
            _window.draw(textReady);
        }

        if (_lobbies[i].name == _lobby && !_lobbies[i].running && _lobbies[i].nbPlayers == _lobbies[i].ready && _lobbies[i].nbPlayers) {
            _window.draw(_lobbies[i].start);
            _window.draw(textStart);
        }

    }

    _lobbyCreate.setFillColor(sf::Color::Black);
    _lobbyCreate.setOutlineColor(_createActivate ? sf::Color::Blue : sf::Color::White);
    _lobbyCreate.setOutlineThickness(_createActivate ? RECT_THICKNESS + 1 : RECT_THICKNESS);
    _lobbyCreate.setSize({LOBBY_RECT_SIZE_X, LOBBY_RECT_SIZE_Y});
    _lobbyCreate.setPosition({LOBBY_RECT_POS_X, LOBBY_RECT_POS_Y(float(i))});

    sf::Text text;

    text.setPosition({LOBBY_NAME_POS_X, TEXT_START_POS_y(float(i))});
    text.setString(CREATE_TITLE(_newLobbyName));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(TEXT_SIZE);

    sf::Font font;

    font.loadFromFile(FONT_PATH);
    text.setFont(font);

    if (_lobbies.size() != MAX_LOBBIES && _lobby.empty()) {
        _window.draw(_lobbyCreate);
        _window.draw(text);
    }

}
