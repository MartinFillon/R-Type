/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

#include "Clock.hpp"
#include "Network.hpp"
#include "Protocol.hpp"
#include "RegistryWrapper.hpp"
#include "TextureManager.hpp"

#define FRAME_PER_SECONDS(x) (int)(1 / x)

namespace client {

    class Game {

      public:
        Game(sf::RenderWindow &window, Network &network);

        void setRegistry(std::shared_ptr<rtype::RegistryWrapper> &registry);

        int run();

      private:
        int event();
        int display();
        void setupBackground();

        Network &_network;

        sf::RenderWindow &_window;
        std::shared_ptr<rtype::RegistryWrapper> _registry;

        ecs::Clock _clock;
        rtype::TextureManager _textureManager;
    };

    static std::map<sf::Keyboard::Key, unsigned char> moves = {
        {sf::Keyboard::Up, protocol::Direction::UP},
        {sf::Keyboard::Down, protocol::Direction::DOWN},
        {sf::Keyboard::Left, protocol::Direction::LEFT},
        {sf::Keyboard::Right, protocol::Direction::RIGHT},
        {sf::Keyboard::Space, protocol::Direction::Space}
    };

}; // namespace client

#endif /* !GAME_HPP_ */
