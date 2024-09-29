/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Context
*/

#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Registry.hpp"

#define GAME_NAME "R-Type"

namespace ecs {

    class Context {
        public:
            Context();
            ~Context();

            sf::RenderWindow &getRenderWindow();

            int run();

        private:
            void setup();
            void setupPlayer();
            void setupBackground();
            void setupWeapon();
            void setupBasicEnnemies();
            sf::RenderWindow _window;
            Registry _r;
    };
} // namespace ecs

#endif /* !CONTEXT_HPP_ */
