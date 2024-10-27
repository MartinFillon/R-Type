/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position3D
*/

#ifndef POSITION3D_HPP_
#define POSITION3D_HPP_

namespace ecs {
    namespace component {
        struct Position3D {
            int _x;
            int _y;
            int _z;
            bool _changeDirection;
        };
    }; // namespace component
}; // namespace ecs


#endif /* !POSITION3D_HPP_ */
