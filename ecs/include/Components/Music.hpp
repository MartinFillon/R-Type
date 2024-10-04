/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct SoundEffect {
            std::string _pathToMusic;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !MUSIC_HPP_ */
