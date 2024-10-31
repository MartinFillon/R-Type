/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct Velocity {
            double _vx;
            double _vy;
            std::string _name = "Velocity";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !VELOCITY_HPP_ */
