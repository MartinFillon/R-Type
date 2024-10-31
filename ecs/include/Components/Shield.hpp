/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Shield
*/

#ifndef SHIELD_HPP_
#define SHIELD_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct Shield {
            double _shield;
            std::string _name = "Shield";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SHIELD_HPP_ */
