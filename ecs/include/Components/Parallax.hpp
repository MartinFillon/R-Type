/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Parallax
*/

#ifndef PARALAX_HPP_
    #define PARALAX_HPP_

#include <vector>
#include <string>

namespace ecs {
    namespace component {
        struct Parallax {
            bool _value;
            double _speed;
            int _multiplicator;
        };
    };
};

#endif /* !PARALAX_HPP_ */
