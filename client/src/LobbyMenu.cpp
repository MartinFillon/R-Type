/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** LOBBY
*/

#include <iostream>

#include "LobbyMenu.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdlib>
#include <string>
#include "TCPCommunication.hpp"

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

void rtype::client::LobbyMenu::event()
{
    sf::Event event;

    while (_window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            _window.close();
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

        struct Lobby newLobby = { name, std::stoi(nbPlayers), std::stoi(running) };

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

}
