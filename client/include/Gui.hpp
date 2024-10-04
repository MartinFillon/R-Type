/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#define TITLE_FONT "assets/fonts/ARCADE_I.ttf"
#define TEXT_FONT "assets/fonts/OpenSans-Semibold.ttf"
#define BUTTON_PLAY "Play"
#define BUTTON_IP "Enter IP Adress !"
#define BUTTON_QUIT "Quit"
#define BUTTON_OPTIONS "Options"
#define MENU_TITLE "R-Type by MR.PET"
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
#define OFFSET "offset"
#define PARA_SPEED 10.f
#define BG_PATH "assets/sprites/Background/background_2.png"


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Clock.hpp"
#include "Network.hpp"
#include "IContext.hpp"
#include "Registry.hpp"
#include "ComponentFactory.hpp"

#define HOST 1
#define PORT 2
#define NB_ARGS 3
#define SUCCESS 0
#define ERROR 84

namespace rtype {

    class Gui : ecs::IContext {

        public:

            Gui(const std::string &host, const std::string &port);

            void launchMenu();
            void setupGame();
            void setupMenu();

            void start();

            int run() override;

            std::shared_ptr<ecs::Registry> &getRegistry() {
                return _r;
            };

        private:

            Network _network;

            void setupWeapon();
            void setupPlayer();
            void setupCollisons();
            void setupBackground();
            void setupBasicEnnemies();
            void setupDestroy();

            sf::RenderWindow _window;
            std::shared_ptr<ecs::Registry> _r;
            ecs::Clock _drawClock;
            ecs::Clock _systemClock;
            ecs::ComponentFactory _factory;

            // Menu part //

            // text part

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
            float _bgScaleX;
            float _bgScaleY;
            float _bgOffset;

    };

};

#endif /* !GUI_HPP_ */
