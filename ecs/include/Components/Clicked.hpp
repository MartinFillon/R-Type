/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Clicked
*/

#ifndef CLICKED_HPP_
#define CLICKED_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Clicked : public IComponent {
            Clicked(bool value): _value(value) {}
            Clicked() = default;
            bool _value;
            std::string _name = "Clicked";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !CLICKED_HPP_ */
