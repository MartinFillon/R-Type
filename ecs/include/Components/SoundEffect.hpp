/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundEffect
*/

#ifndef SOUNDEFFECT_HPP_
    #define SOUNDEFFECT_HPP_

    #include <SFML/Audio/Music.hpp>
    #include <string>

namespace ecs {
    namespace component {
        struct SoundEffect {
            sf::Music _sound;
            std::string _pathToSound;
        };
    };
};

#endif /* !SOUNDEFFECT_HPP_ */
