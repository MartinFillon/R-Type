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
        int ready;
        sf::RectangleShape rectangle;
        sf::RectangleShape buttonReady;
        sf::RectangleShape join;
        sf::RectangleShape start;
    };

    class LobbyMenu {

        public:

            LobbyMenu(sf::RenderWindow &window);

            int launchLobby(std::shared_ptr<TCPCommunication> server);

        private:

            void setup();
            void setupBackground();
            void setupLoadingGame();

            void display();
            void displayLobbies();

            void event();
            void createNewLobby(sf::Event &event);

            void update();
            void updateBackground();
            void updateLobbies();

            void loadingGame();

            bool _running;

            sf::RenderWindow &_window;
            std::vector<Lobby> _lobbies;

            std::string _lobby;
            bool _ready;

            int _port;

            std::shared_ptr<TCPCommunication> _server;

            /* LOADIN GAME */
            bool _loading;
            float _loadingValue;
            int _loadingStop;
            sf::RectangleShape _loadingRectangle;
            sf::RectangleShape _loadingPourcent;
            sf::Text _loadingText;

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
