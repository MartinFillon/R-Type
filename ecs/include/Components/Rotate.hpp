/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Rotate
*/

#ifndef ROTATE_HPP_
#define ROTATE_HPP_

#include <string>
#include "Components/IComponent.hpp"

namespace ecs {
    namespace component {
        struct Rotate : public IComponent {
            Rotate(int pitch, int yaw, int roll): _pitch(pitch), _yaw(yaw), _roll(roll) {}
            Rotate() = default;
            int _pitch;
            int _yaw;
            int _roll;
            std::string _name = "Rotate";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ROTATE_HPP_ */
