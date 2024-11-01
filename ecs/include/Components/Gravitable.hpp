/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Gravitable
*/

#ifndef GRAVITABLE_HPP_
#define GRAVITABLE_HPP_

#include <sstream>
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
            std::string getInfo() const {
                std::ostringstream stream;

                stream << "Value: " + std::string(_value ? "true" : "false") << " Gravity Fall: " << _gravityFall;
                stream << " is Jumping: " << std::string(_isJumping ? "true": "false") << " is Falling: " << std::string(_isFalling ? "true": "false");

                return stream.str();
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !GRAVITABLE_HPP_ */
