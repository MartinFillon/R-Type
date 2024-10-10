/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundEffect
*/

#ifndef SOUNDEFFECT_HPP_
#define SOUNDEFFECT_HPP_

#include <string>

namespace ecs {
    namespace component {
        /// @brief SoundEffect Component, that stored a path to the Sound Effect as a string
        struct SoundEffect {
            std::string _pathToSound;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SOUNDEFFECT_HPP_ */
