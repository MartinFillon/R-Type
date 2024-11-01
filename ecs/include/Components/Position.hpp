/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <sstream>
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
            std::string getInfo() const {
                std::ostringstream stream;
                
                stream << "x: " << _x;
                stream << " y: " << _y;
                stream << " changing: " << std::string(_changeDirection ? "true": "false");

                return stream.str();
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !POSITION_HPP_ */
