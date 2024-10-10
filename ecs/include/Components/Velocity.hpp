/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

namespace ecs {
    namespace component {
        /// @brief Velocity Component, to have the velocity of an entity, it stored velocity x and y as a double
        struct Velocity {
            double _vx;
            double _vy;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !VELOCITY_HPP_ */
