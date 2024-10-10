/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <memory>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>

    #include "Clock.hpp"
    #include "Network.hpp"
    #include "Registry.hpp"
    #include "Protocol.hpp"
    #include "TextureManager.hpp"
    #include "ComponentFactory.hpp"

    #define FRAME_PER_SECONDS(x) (int)(1 / x)

namespace client {

    class Game {

        public:

            Game(sf::RenderWindow &window, Network &network);

            void setRegistry(std::shared_ptr<ecs::Registry> registry);

            int run();

        private:

            int event();
            int display();

            Network &_network;

            sf::RenderWindow &_window;
            std::shared_ptr<ecs::Registry> _registry;

            ecs::Clock _clock;
            rtype::TextureManager _textureManager;

    };

    static std::map<sf::Keyboard::Key, unsigned char> moves = {
        { sf::Keyboard::Up,     protocol::Direction::UP       },
        { sf::Keyboard::Down,   protocol::Direction::DOWN     },
        { sf::Keyboard::Left,   protocol::Direction::LEFT     },
        { sf::Keyboard::Right,  protocol::Direction::RIGHT    }
    };

};

#endif /* !GAME_HPP_ */
