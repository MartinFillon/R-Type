/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Shield
*/

#ifndef SHIELD_HPP_
#define SHIELD_HPP_

#include <sstream>
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
            std::string getInfo() const {
                std::ostringstream stream;

                stream << _shield;

                return stream.str();
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SHIELD_HPP_ */
