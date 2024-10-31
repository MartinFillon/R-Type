/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Shield
*/

#ifndef SHIELD_HPP_
#define SHIELD_HPP_

#include <string>
#include "Components/IComponent.hpp"

namespace ecs {
    namespace component {
        struct Shield : public IComponent {
            Shield(double shield): _shield(shield) {}
            Shield() = default;
            double _shield;
            std::string _name = "Shield";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SHIELD_HPP_ */
