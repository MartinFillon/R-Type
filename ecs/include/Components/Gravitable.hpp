/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Gravitable
*/

#ifndef GRAVITABLE_HPP_
#define GRAVITABLE_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Gravitable : public IComponent{
            Gravitable(bool value, int gravityFall, bool isJumping, bool isFalling): _value(value), _gravityFall(gravityFall), _isJumping(isJumping), _isFalling(isFalling) {}
            Gravitable() = default;
            bool _value;
            int _gravityFall;
            bool _isJumping;
            bool _isFalling;
            std::string _name = "Gravitable";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !GRAVITABLE_HPP_ */
