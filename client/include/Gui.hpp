/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#ifndef GUI_HPP_
#define GUI_HPP_

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


      protected:
      private:
        sf::RenderWindow &getRenderWindow();

        void setupGame();
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

        // Menu part

        sf::Font _font;
        sf::Text _menuText[3];
        bool _isLogin;
        bool _isQuitPress;
        bool _isMenuOpen;

    };
} // namespace rtype

#endif /* !GUI_HPP_ */
