/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

#include <sstream>
#include <string>
#include "Components/IComponent.hpp"

namespace ecs {
    namespace component {
        struct Velocity : public IComponent {
            Velocity(double vx, double vy): _vx(vx), _vy(vy) {}
            Velocity() = default;
            double _vx;
            double _vy;
            std::string _name = "Velocity";
            std::string getName() const {
                return _name;
            }
            std::string getInfo() const {
                std::ostringstream stream;
                
                stream << "Vx: " << _vx << " Vy:" << _vy;

                return stream.str();
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !VELOCITY_HPP_ */
