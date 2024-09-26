/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Controllable
*/

#ifndef CONTROLLABLE_HPP_
    #define CONTROLLABLE_HPP_

namespace ecs {
    namespace component {
        struct Controllable {
            bool _controllable;
            double _speed;
        };
    };
};

#endif /* !CONTROLLABLE_HPP_ */
