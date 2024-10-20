/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** KeyPressed
*/

#ifndef KEYPRESSED_HPP_
#define KEYPRESSED_HPP_

namespace ecs {
    namespace component {
        enum Key { NoneKey, Up, Down, Right, Left };
        struct KeyPressed {
            Key _value;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !KEYPRESSED_HPP_ */
