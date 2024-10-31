/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <string>
namespace ecs {
    namespace component {
        struct Position {
            int _x;
            int _y;
            bool _changeDirection;
            std::string _name = "Position";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !POSITION_HPP_ */
