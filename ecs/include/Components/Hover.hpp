/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hover
*/

#ifndef HOVER_HPP_
#define HOVER_HPP_

#include <string>
namespace ecs {
    namespace component {
        struct Hover {
            bool _value;
            std::string _name = "Hover";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !HOVER_HPP_ */
