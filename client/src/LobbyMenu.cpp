/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** LOBBY
*/

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

#include "LobbyMenu.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdlib>
#include <string>
#include "TCPCommunication.hpp"
#include "asio/write.hpp"

rtype::client::LobbyMenu::LobbyMenu(sf::RenderWindow &window): _running(true), _window(window)
{

}

int rtype::client::LobbyMenu::launchLobby(std::shared_ptr<TCPCommunication> server)
{
    _server = std::move(server);
    setup();

    while (_running && _window.isOpen()) {

        event();
        update();
        display();

    }

    return EXIT_SUCCESS;
}

void rtype::client::LobbyMenu::setup()
{
    setupBackground();
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
                    }
                    continue;
                }

                if (_lobby.empty() && _lobbies[i].join.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    _server.get()->send("JOIN " + _lobbies[i].name + "\n");
                    if (_server.get()->read().find("200") != std::string::npos) {
                        _lobby = _lobbies[i].name;
                    }
                    continue;
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

    while (lobby.find("200") == std::string::npos) {

        std::string name = lobby.substr(0, lobby.find(':'));
        std::string running = lobby.substr(lobby.find(':') + 1, 1);
        std::string nbPlayers = lobby.substr(lobby.find(':') + 3, 1);

        std::cout << "NAME: [" << name << "]\n";

        struct Lobby newLobby = { name, std::stoi(nbPlayers), std::stoi(running), sf::RectangleShape(), sf::RectangleShape()};

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

        _lobbies[i].join.setFillColor(sf::Color::Black);
        _lobbies[i].join.setOutlineColor(_lobby.empty() ? sf::Color::Green : sf::Color::Red);
        _lobbies[i].join.setOutlineThickness(2);
        _lobbies[i].join.setSize({130, 80});
        _lobbies[i].join.setPosition({1240, 240 + (float)i * 140});

        sf::Text text;

        text.setPosition({620, 250 + (float)i * 140});
        text.setString(_lobbies[i].name);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(42);

        sf::Text textJoin;

        textJoin.setPosition({1260 - (float)!_lobby.empty() * 5, 250 + (float)i * 140});
        textJoin.setString(_lobby.empty() ? "JOIN" : "QUIT");
        textJoin.setFillColor(_lobby.empty() ? sf::Color::Green: sf::Color::Red);
        textJoin.setCharacterSize(42);

        sf::Text nbPlayers;

        nbPlayers.setPosition({1090, 255 + (float)i * 140});
        nbPlayers.setString(std::to_string(_lobbies[i].nbPlayers) + " / 4");
        nbPlayers.setFillColor(_lobbies[i].nbPlayers < 4 ? sf::Color::Green : sf::Color::Red);
        nbPlayers.setCharacterSize(42);

        sf::Font font;

        font.loadFromFile("./assets/fonts/OpenSans-Semibold.ttf");
        text.setFont(font);
        nbPlayers.setFont(font);
        textJoin.setFont(font);

        _window.draw(_lobbies[i].rectangle);
        _window.draw(text);
        _window.draw(nbPlayers);

        if (_lobby.empty() && _lobbies[i].nbPlayers != 4 && _lobbies[i].running == false) {
            _window.draw(_lobbies[i].join);
            _window.draw(textJoin);
        }

        if (_lobby == _lobbies[i].name) {
            _window.draw(_lobbies[i].join);
            _window.draw(textJoin);
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
