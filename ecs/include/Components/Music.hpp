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
        /// @brief Music Component, that stored a path to the music as a string
        struct Music {
            std::string _pathToMusic;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !MUSIC_HPP_ */
