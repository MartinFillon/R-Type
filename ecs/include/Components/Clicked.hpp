/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Clicked
*/

#ifndef CLICKED_HPP_
#define CLICKED_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct Clicked {
            bool _value;
            std::string _name = "Clicked";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !CLICKED_HPP_ */
