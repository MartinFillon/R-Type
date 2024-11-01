/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position3D
*/

#ifndef POSITION3D_HPP_
#define POSITION3D_HPP_

#include <sstream>
#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Position3D : public IComponent {
            Position3D(int x, int y, int z, bool changeDirection): _x(x), _y(y), _z(z), _changeDirection(changeDirection) {}
            Position3D(int x, int y, int z): _x(x), _y(y), _z(z), _changeDirection(false) {}
            Position3D() = default;
            int _x;
            int _y;
            int _z;
            bool _changeDirection;
            std::string _name = "Position3D";
            std::string getName() const {
                return _name;
            }
            std::string getInfo() const {
                std::ostringstream stream;
                
                stream << "x: " << _x;
                stream << " y: " << _y;
                stream << " z: " << _z;
                stream << " changing: " << std::string(_changeDirection ? "true": "false");

                return stream.str();
            }
        };
    }; // namespace component
}; // namespace ecs


#endif /* !POSITION3D_HPP_ */
