/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Cinematic
*/

#ifndef CINEMATIC_HPP_
#define CINEMATIC_HPP_

#include "Components/Attributes.hpp"
#include "Components/Position.hpp"

namespace ecs {
    namespace component {
        struct Cinematic {
            Position _start;
            Position _end;
            Attributes _atr;
            bool _state;
            int _speed;
            std::string _name = "Cinematic";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !CINEMATIC_HPP_ */
