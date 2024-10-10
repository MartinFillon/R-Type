/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

namespace ecs {
    namespace component {
        /// @brief Position Component, to store the position of the entity, it store as an integer the x and y, and a boolean to know if it change of direction, useful for the milespates or entities that changes directions alone
        struct Position {
            int _x;
            int _y;
            bool _changeDirection;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !POSITION_HPP_ */
