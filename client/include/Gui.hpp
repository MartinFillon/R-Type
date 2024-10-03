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


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Clock.hpp"
#include "ComponentFactory.hpp"
#include "IContext.hpp"
#include "Registry.hpp"

namespace rtype {
    class Gui : ecs::IContext {
      public:
        Gui();
        ~Gui();

        int run() override;
        void launchMenu();
        void setupGame();
        void setupMenu();


      protected:
      private:
        sf::RenderWindow &getRenderWindow();

        void setupPlayer();
        void setupBackground();
        void setupWeapon();
        void setupBasicEnnemies();
        std::shared_ptr<ecs::Registry> _r;
        ecs::Clock _drawClock;
        ecs::Clock _systemClock;
        sf::RenderWindow _window;
        void setupCollisons();
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

    };
} // namespace rtype

#endif /* !GUI_HPP_ */
