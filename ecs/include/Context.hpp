/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Context
*/

#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#define UNABLE_TO_LOAD_TEXTURE(texture) "Unable to load the texture: " + texture

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <exception>
#include "Registry.hpp"

#define GAME_NAME "R-Type"

namespace ecs {

    class Context {
        public:
            Context();
            ~Context();

            class ContextException : public std::exception {
                public:
                    ContextException(const std::string &error): _what(error) {}
                    ~ContextException() = default;

                    const char *what() const noexcept
                    {
                        return _what.c_str();
                    }
                private:
                    std::string _what;
            };
            sf::RenderWindow &getRenderWindow();

            int run();

        private:
            void setup();
            void setupPlayer();
            void setupBackground();
            void setupWeapon();
            void setupBasicEnnemies();
            void setupCollision();
            sf::RenderWindow _window;
            Registry _r;
    };
} // namespace ecs

#endif /* !CONTEXT_HPP_ */
