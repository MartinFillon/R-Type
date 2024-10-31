/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Parallax
*/

#ifndef PARALAX_HPP_
#define PARALAX_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Parallax : public IComponent {
            Parallax(int value, double speed, int multiplicator): _value(value), _speed(speed), _multiplicator(multiplicator) {}
            Parallax() = default;
            bool _value;
            double _speed;
            int _multiplicator;
            std::string _name = "Parallax";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !PARALAX_HPP_ */
