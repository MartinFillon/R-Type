/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Parallax
*/

#ifndef PARALAX_HPP_
#define PARALAX_HPP_

#include <string>
namespace ecs {
    namespace component {
        struct Parallax {
            bool _value;
            double _speed;
            int _multiplicator;
            std::string _name = "Parallax";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !PARALAX_HPP_ */
