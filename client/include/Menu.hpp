/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Menu class
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>

#define TITLE_FONT "assets/fonts/ARCADE_I.ttf"
#define TEXT_FONT "assets/fonts/OpenSans-Semibold.ttf"
#define BUTTON_PLAY "Play"
#define BUTTON_IP "Enter IP Adress !"
#define BUTTON_QUIT "Quit"
#define BUTTON_OPTIONS "Options"
#define MENU_TITLE "R-Type by MR.PET"
#define BG_PATH "assets/sprites/Background/background_2.png"
#define OFFSET "offset"
#define EMPTY_ADRESS "empty adress"
#define MENU_MUSIC "assets/musics/menuMusic.ogg"
#define BG_POS_X 0
#define BG_POS_Y 0
#define NB_TITLES 5
#define BORDER_RECT_PRESS 3.5
#define BORDER_RECT_NO_PRESS 0
#define CASE_PLAY 0
#define CASE_OPTIONS 1
#define CASE_QUIT 2
#define ASCII_LIM 128
#define NON_ASCII_CHAR 31
#define DEL_BUTTON 8
#define LEFT_MARGE 800
#define PLAY_POS_X 400
#define IP_POS_X 460
#define OPTIONS_POS_X 550
#define IP_RECT_POS_X 495
#define QUIT_POS_X 625
#define TITLE_POS_X 200
#define TITLE_POS_Y 450
#define TEXT_POS_X 500
#define FONT_SIZE_TITLE 70
#define FONT_SIZE_IP 17
#define FONT_SIZE_INPUT 15
#define RECT_SIZE_X 30
#define RECT_SIZE_Y 300
#define PARA_SPEED 10.f

namespace rtype::client {

    class Menu {

      public:
        Menu(sf::RenderWindow &window);

        void setupMenu();
        void setupBackground();
        void setupMenuFont();
        void setupMenuInputRect();
        void setupPlayButton();
        void setupOptionsButton();
        void setupQuitButton();
        void setupMenuTitle();
        void setupIpButton();
        void setupRenderFont();

        void menuCloseWindow(sf::Event &event);
        void menuEnterToPlay();
        void menuTextEntered(sf::Event &event);
        void menuShaderParams(sf::Shader &para);

        int menuLoadShader();

        void menuDrawtitles();
        void menuDraw(sf::Shader &para);

        std::string menuButtonPressed();
        std::string launchMenu();

      private:
        sf::RenderWindow &_win;

        // font //
        sf::Font _fontTitle;
        sf::Font _fontText;
        sf::Text _menutitle[5];

        // Log part

        sf::RectangleShape _ipRect;
        sf::Text _menuDisplayInput;
        std::string _menuClientInput;
        char _inputChar;

        // menu or ?

        bool _isWritting;
        bool _isLogin;
        bool _isQuitPress;
        bool _isMenuOpen;

        // background

        sf::Clock _menuClock;
        sf::Texture _backgroundTexture;
        sf::Sprite _backgroundSprite;
        sf::Shader _para;
        float _bgScaleX;
        float _bgScaleY;
        float _bgOffset;
    };

}; // namespace rtype::client

#endif /* !MENU_HPP_ */
