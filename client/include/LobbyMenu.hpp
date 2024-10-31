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

#define OFFSET "offset"
#define START_TITLE "START"
#define JOIN_TITLE "JOIN"
#define QUIT_TITLE "QUIT"
#define READY_TITLE "READY"
#define CREATE_TITLE(x) "Create lobby : " + x
#define LOADING_TITLE(x) "Loading " + x + "%"

#define BG_PATH "./assets/sprites/Background/background_2.png"
#define FONT_PATH "./assets/fonts/OpenSans-Semibold.ttf"

#define CREATE_CMD(x) "CREATE " + x + "\n"
#define QUIT_CMD(x) "QUIT " + x + "\n"
#define JOIN_CMD(x) "JOIN " + x + "\n"
#define READY_CMD "READY\n"
#define UNREADY_CMD "UNREADY\n"
#define START_CMD "START\n"
#define LIST_CMD "LIST\n"

#define NETWORK_METHOD_GAME "UDP"
#define TOKEN_PARSE_NETWORK ':'
#define LOBBY_MAX_PLAYERS " / 4"

#define PARALAX_SPEED 10.
#define ASCII_LIM 128
#define NON_ASCII_CHAR 31
#define DEL_BUTTON 8

#define BG_POS_Y 0
#define BG_POS_X 0
#define RECT_THICKNESS 2

#define START_BUTTON_SIZE_X 160
#define START_BUTTON_SIZE_Y 80
#define START_BUTTON_POS_X 400
#define START_BUTTON_POS_Y(x) 240 + x * 140

#define JOIN_BUTTON_SIZE_X 130
#define JOIN_BUTTON_SIZE_Y 80
#define JOIN_BUTTON_POS_X 1240
#define JOIN_BUTTON_POS_Y(x) 240 + x * 140

#define READY_BUTTON_SIZE_X 160
#define READY_BUTTON_SIZE_Y 80
#define READY_BUTTON_POS_X 1407
#define READY_BUTTON_POS_Y(x) 240 + x * 140

#define LOADING_RECT_SIZE_X 600
#define LOADING_RECT_SIZE_Y 80
#define LOADING_RECT_POS_X 600
#define LOADING_RECT_POS_Y 480

#define LOBBY_RECT_SIZE_X 600
#define LOBBY_RECT_SIZE_Y 80
#define LOBBY_RECT_POS_X 600
#define LOBBY_RECT_POS_Y(x) 240 + x * 140

#define PERCENT_RECT_SIZE_X 600
#define PERCENT_RECT_SIZE_Y 80
#define PERCENT_RECT_POS_X 600
#define PERCENT_RECT_POS_Y 480

#define LOADING_TEXT_POS_X 600
#define LOADING_TEXT_POS_Y 420
#define LOBBY_NAME_POS_X 620
#define LOBBY_NAME_POS_Y(x) 250 + x * 140

#define TEXT_START_POS_X 417
#define TEXT_START_POS_y(x) 250 + x * 140

#define TEXT_JOIN_POS_X(x) 1260 - x * 5
#define TEXT_JOIN_POS_Y(x) 250 + x * 140

#define TEXT_READY_POS_X 1422
#define TEXT_READY_POS_Y(x) 250 + x * 140

#define TEXT_NB_P_POS_X 1090
#define TEXT_NB_P_POS_Y(x) 255 + x * 140

#define LOBBY_NAME_POS_X 620
#define TEXT_SIZE 42
#define MAX_LOADING_VALUE 100
#define LOADING_STOP 1000
#define FUN_STOP 42.0
#define RESET_STOP 0
#define LOADING_LOAD_VALUE 0.08
#define PERCENT_SIZE_ADAPT 6
#define MAX_LOBBIES 4
#define STOP_START_VALIUE 1
#define TIME_STOP 1

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
        void createNewLobby(const sf::Event::TextEntered *event);

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
        // sf::Text _loadingText;

        /* CREATE LOBBY BUTTON */

        sf::RectangleShape _lobbyCreate;
        std::string _newLobbyName;
        bool _createActivate;

        /* BACKGROUND MENU */

        sf::Shader _shader;
        sf::Clock _backgroundClock;
        // sf::Sprite _backgroundSprite;
        sf::Texture _backgroundTexture;

        float _bgScaleX;
        float _bgScaleY;
        float _bgOffset;
    };

}; // namespace rtype::client

#endif /* !LOBBYMENU_HPP_ */
