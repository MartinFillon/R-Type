/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Position : public IComponent {
            Position(int x, int y, bool changeDirection): _x(x), _y(y), _changeDirection(changeDirection) {}
            Position(int x, int y): _x(x), _y(y), _changeDirection(false) {}
            Position() = default;
            int _x;
            int _y;
            bool _changeDirection;
            std::string _name = "Position";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !POSITION_HPP_ */
