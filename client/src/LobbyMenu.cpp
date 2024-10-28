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
#include "TCPCommunication.hpp"

#include <iostream>

rtype::client::LobbyMenu::LobbyMenu(sf::RenderWindow &window): _running(true), _window(window), _ready(false), _loading(true)
{

}

int rtype::client::LobbyMenu::launchLobby(std::shared_ptr<TCPCommunication> server)
{
    _server = std::move(server);
    setup();

    while (_running && _window.isOpen() && _server->getPort() == 0) {

        update();
        display();
        event();

    }

    setupLoadingGame();

    while (_window.isOpen() && _loading) {
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
    _loadingRectangle.setOutlineThickness(2);
    _loadingRectangle.setSize({600, 80});
    _loadingRectangle.setPosition({600, 480});

    _loadingPourcent.setFillColor(sf::Color::Green);
    _loadingPourcent.setSize({600, 80});
    _loadingPourcent.setPosition({600, 480});

    _loadingText.setPosition({600, 420});
    _loadingText.setString("Loading " + std::to_string(_loadingValue) + "%");
    _loadingText.setFillColor(sf::Color::White);
    _loadingText.setCharacterSize(42);

    _loadingStop = 1;
}

void rtype::client::LobbyMenu::loadingGame()
{
    _window.clear();

    updateBackground();

    if (_loadingValue >= 100) {
        _loading = false;
        return;
    }

    if (_loadingValue >= 42.0 && _loadingStop) {
        _loadingStop += 1;
        if (_loadingStop == 1000) {
            _loadingStop = 0;
        }
    }

    if (_loadingStop == 1 || _loadingStop == 0) {
        _loadingValue += 0.08;
    }
    
    sf::Font font;

    _window.draw(_backgroundSprite, &_shader);

    font.loadFromFile("./assets/fonts/OpenSans-Semibold.ttf");
    _loadingText.setFont(font);

    _loadingPourcent.setSize({_loadingValue * 6, 80});
    _loadingText.setString("Loading " + std::to_string((int)_loadingValue) + "%");

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

    if (event.text.unicode < 128) {
        _inputChar = static_cast<char>(event.text.unicode);
        if (_inputChar == 8 && !_newLobbyName.empty()) {
            _newLobbyName.pop_back();
        } else if (_inputChar > 31 && _inputChar < 128) {
            _newLobbyName += _inputChar;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !_newLobbyName.empty()) {
        _server.get()->send("CREATE " + _newLobbyName + "\n");
        _server.get()->read();
        _newLobbyName.clear();
    }
}

void rtype::client::LobbyMenu::event()
{
    sf::Event event;

    while (_window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            _window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mouse = sf::Mouse::getPosition(_window);

            if (_lobbyCreate.getGlobalBounds().contains(mouse.x, mouse.y)) {
                _createActivate = !_createActivate;
            } else {
                _createActivate = false;
            }

            for (int i = 0; i < _lobbies.size(); i++) {
                if (!_lobby.empty() && _lobbies[i].join.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    _server.get()->send("QUIT " + _lobbies[i].name + "\n");
                    if (_server.get()->read().find("200") != std::string::npos) {
                        _lobby.clear();
                        _ready = false;
                    }
                    continue;
                }

                if (!_lobbies[i].running && _lobby.empty() && _lobbies[i].join.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    _server.get()->send("JOIN " + _lobbies[i].name + "\n");
                    if (_server.get()->read().find("200") != std::string::npos) {
                        _lobby = _lobbies[i].name;
                        _ready = false;
                    }
                    continue;
                }

                if (!_lobby.empty() && _lobbies[i].buttonReady.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    if (!_ready) {
                        _server.get()->send("READY\n");
                        if (_server.get()->read().find("200") != std::string::npos) {
                            _ready = true;
                        }
                        continue;
                    }

                    if (_ready) {
                        _server.get()->send("UNREADY\n");
                        if (_server.get()->read().find("200") != std::string::npos) {
                            _ready = false;
                        }
                        continue;
                    }
                }

                if (_lobbies[i].name == _lobby && _lobbies[i].nbPlayers == _lobbies[i].ready && _lobbies[i].nbPlayers && _lobbies[i].start.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    _server.get()->send("START\n");
                    std::string response = _server.get()->read();
                    if (response.find("UDP") != std::string::npos) {
                        _running = false;
                        _port = std::stoi(response.substr(response.find(':') + 1));
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
    _server.get()->send("LIST\n");

    std::string lobby = _server.get()->read();

    _lobbies.clear();

    while (lobby.find("200") == std::string::npos && lobby.find("UDP") == std::string::npos) {

        std::string name = lobby.substr(0, lobby.find(':'));
        std::string running = lobby.substr(lobby.find(':') + 1, 1);
        std::string nbPlayers = lobby.substr(lobby.find(':') + 3, 1);
        std::string ready = lobby.substr(lobby.find(':') + 5, 1);

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
        _lobbies[i].rectangle.setOutlineThickness(2);
        _lobbies[i].rectangle.setSize({600, 80});
        _lobbies[i].rectangle.setPosition({600, 240 + (float)i * 140});

        _lobbies[i].start.setFillColor(sf::Color::Black);
        _lobbies[i].start.setOutlineColor(sf::Color::Green);
        _lobbies[i].start.setOutlineThickness(2);
        _lobbies[i].start.setSize({160, 80});
        _lobbies[i].start.setPosition({400, 240 + (float)i * 140});

        _lobbies[i].join.setFillColor(sf::Color::Black);
        _lobbies[i].join.setOutlineColor(_lobby.empty() ? sf::Color::Green : sf::Color::Red);
        _lobbies[i].join.setOutlineThickness(2);
        _lobbies[i].join.setSize({130, 80});
        _lobbies[i].join.setPosition({1240, 240 + (float)i * 140});

        _lobbies[i].buttonReady.setFillColor(sf::Color::Black);
        _lobbies[i].buttonReady.setOutlineColor(_ready ? sf::Color::Green : sf::Color::Red);
        _lobbies[i].buttonReady.setOutlineThickness(2);
        _lobbies[i].buttonReady.setSize({160, 80});
        _lobbies[i].buttonReady.setPosition({1407, 240 + (float)i * 140});

        sf::Text text;

        text.setPosition({620, 250 + (float)i * 140});
        text.setString(_lobbies[i].name);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(42);

        sf::Text textStart;

        textStart.setPosition({417, 250 + (float)i * 140});
        textStart.setString("START");
        textStart.setFillColor(sf::Color::Green);
        textStart.setCharacterSize(42);

        sf::Text textJoin;

        textJoin.setPosition({1260 - (float)!_lobby.empty() * 5, 250 + (float)i * 140});
        textJoin.setString(_lobby.empty() ? "JOIN" : "QUIT");
        textJoin.setFillColor(_lobby.empty() ? sf::Color::Green: sf::Color::Red);
        textJoin.setCharacterSize(42);

        sf::Text textReady;

        textReady.setPosition({1422, 250 + (float)i * 140});
        textReady.setString("READY");
        textReady.setFillColor(_ready ? sf::Color::Green: sf::Color::Red);
        textReady.setCharacterSize(42);

        sf::Text nbPlayers;

        nbPlayers.setPosition({1090, 255 + (float)i * 140});
        nbPlayers.setString(std::to_string(_lobbies[i].nbPlayers) + " / 4");
        nbPlayers.setFillColor(_lobbies[i].nbPlayers == _lobbies[i].ready && _lobbies[i].nbPlayers ? sf::Color::Green : sf::Color::White);
        nbPlayers.setCharacterSize(42);

        sf::Font font;

        font.loadFromFile("./assets/fonts/OpenSans-Semibold.ttf");
        text.setFont(font);
        nbPlayers.setFont(font);
        textJoin.setFont(font);
        textReady.setFont(font);
        textStart.setFont(font);

        _window.draw(_lobbies[i].rectangle);
        _window.draw(text);
        _window.draw(nbPlayers);

        if (!_lobbies[i].running && _lobby.empty() && _lobbies[i].nbPlayers != 4 && _lobbies[i].running == false) {
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
    _lobbyCreate.setOutlineThickness(_createActivate ? 3 : 2);
    _lobbyCreate.setSize({600, 80});
    _lobbyCreate.setPosition({600, 240 + (float)i * 140});

    sf::Text text;

    text.setPosition({620, 250 + (float)i * 140});
    text.setString("Create lobby: " + _newLobbyName);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(42);

    sf::Font font;

    font.loadFromFile("./assets/fonts/OpenSans-Semibold.ttf");
    text.setFont(font);

    if (_lobbies.size() != 4 && _lobby.empty()) {
        _window.draw(_lobbyCreate);
        _window.draw(text);
    }

}
