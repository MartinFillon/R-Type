/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Parallax
*/

#ifndef PARALAX_HPP_
#define PARALAX_HPP_

namespace ecs {
    namespace component {
        struct Parallax {
            bool _value;
            double _speed;
            int _multiplicator;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !PARALAX_HPP_ */
