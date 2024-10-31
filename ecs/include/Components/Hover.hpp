/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hover
*/

#ifndef HOVER_HPP_
#define HOVER_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Hover : public IComponent {
            Hover(bool value): _value(value) {}
            Hover() = default;
            bool _value;
            std::string _name = "Hover";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !HOVER_HPP_ */
