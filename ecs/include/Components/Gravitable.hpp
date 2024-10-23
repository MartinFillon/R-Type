/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Gravitable
*/

#ifndef GRAVITABLE_HPP_
#define GRAVITABLE_HPP_

namespace ecs {
    namespace component {
        struct Gravitable {
            bool _value;
            int _gravityFall;
            bool _isJumping;
            bool _isFalling;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !GRAVITABLE_HPP_ */
