/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Rotate
*/

#ifndef ROTATE_HPP_
#define ROTATE_HPP_

namespace ecs {
    namespace component {
        struct Rotate {
            int pitch;
            int yaw;
            int roll;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ROTATE_HPP_ */
