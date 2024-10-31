/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Controllable
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Controllable : public IComponent {
            Controllable(bool controllable, double speed): _controllable(controllable), _speed(speed) {}
            Controllable() = default;
            bool _controllable;
            double _speed;
            std::string _name = "Controllable";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !CONTROLLABLE_HPP_ */
