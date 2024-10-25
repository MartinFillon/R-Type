/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** LOBBY
*/

#ifndef LOBBYMENU_HPP_
    #define LOBBYMENU_HPP_

    #include <SFML/Graphics.hpp>
    #include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

    #include "TCPCommunication.hpp"

    #define BG_POS_X 0
    #define BG_POS_Y 0
    #define OFFSET "offset"
    #define PARALAX_SPEED 10.0
    #define BG_PATH "./assets/sprites/Background/background_2.png"

namespace rtype::client {

    struct Lobby {
        std::string name;
        int nbPlayers;
        int running;
        sf::RectangleShape rectangle;
    };

    class LobbyMenu {

        public:

            LobbyMenu(sf::RenderWindow &window);

            int launchLobby(std::shared_ptr<TCPCommunication> server);

        private:

            void setup();
            void setupBackground();

            void display();
            void displayLobbies();

            void event();
            void createNewLobby(sf::Event &event);

            void update();
            void updateBackground();
            void updateLobbies();

            bool _running;

            sf::RenderWindow &_window;
            std::vector<Lobby> _lobbies;

            std::shared_ptr<TCPCommunication> _server;

            /* CREATE LOBBY BUTTON */

            sf::RectangleShape _lobbyCreate;
            std::string _newLobbyName;
            bool _createActivate;

            /* BACKGROUND MENU */

            sf::Shader _shader;
            sf::Clock _backgroundClock;
            sf::Sprite _backgroundSprite;
            sf::Texture _backgroundTexture;

            float _bgScaleX;
            float _bgScaleY;
            float _bgOffset;

    };

};

#endif /* !LOBBYMENU_HPP_ */
