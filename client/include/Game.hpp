/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "ComponentFactory.hpp"
#define SHOOT_SOUND "assets/musics/shotSound.ogg"
#define GAME_MUSIC "assets/musics/gameMusic-Thrut.ogg"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <memory>

#include "Clock.hpp"
#include "Network.hpp"
#include "Protocol.hpp"
#include "RegistryWrapper.hpp"
#include "TextureManager.hpp"

#define FRAME_PER_SECONDS(x) (int)(1 / x)

namespace rtype::client {
    class Game {
      public:
        Game(sf::RenderWindow &window, Network &network);

        void setRegistry(std::shared_ptr<RegistryWrapper> &registry);

        void setFactory(std::shared_ptr<ecs::ComponentFactory> &cf)
        {
            _cf = cf;
        }

        int run();

      private:
        void event();
        void display();
        void setupBackground();
        void setupSound();
        void launchMusic();

        Network &_network;

        sf::RenderWindow &_window;
        std::shared_ptr<RegistryWrapper> _registry;
        std::shared_ptr<ecs::ComponentFactory> _cf;

        ecs::Clock _clock;
        TextureManager _textureManager;

        sf::SoundBuffer _gameShotSoundBuffer;
        sf::Sound _shotSound;

        sf::SoundBuffer _gameMusicBuffer;
        sf::Sound _gameSound;
    };

    static std::map<sf::Keyboard::Key, unsigned char> moves = {
        {sf::Keyboard::Up, protocol::Direction::UP},
        {sf::Keyboard::Down, protocol::Direction::DOWN},
        {sf::Keyboard::Left, protocol::Direction::LEFT},
        {sf::Keyboard::Right, protocol::Direction::RIGHT},
        {sf::Keyboard::Space, protocol::Direction::Space}
    };
}; // namespace rtype::client
#endif /* !GAME_HPP_ */
