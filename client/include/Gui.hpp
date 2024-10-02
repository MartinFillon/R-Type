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
    };
} // namespace rtype

#endif /* !GUI_HPP_ */
