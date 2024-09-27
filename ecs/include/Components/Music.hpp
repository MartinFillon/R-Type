/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <SFML/Audio/Music.hpp>
#include <string>

namespace ecs {
    namespace component {
        struct SoundEffect {
            sf::Music _music;
            std::string _pathToMusic;
        };
    }; // namespace component
};     // namespace ecs

#endif /* !MUSIC_HPP_ */
