/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundEffect
*/

#ifndef SOUNDEFFECT_HPP_
#define SOUNDEFFECT_HPP_

#include <string>
#include "Components/IComponent.hpp"

namespace ecs {
    namespace component {
        struct SoundEffect : public IComponent {
            SoundEffect(std::string pathToSound): _pathToSound(pathToSound) {}
            SoundEffect() = default;
            std::string _pathToSound;
            std::string _name = "SoundEffect";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SOUNDEFFECT_HPP_ */
