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
        struct Cinematic : public IComponent {
            Cinematic(Position start, Position end, Attributes attr, bool state, int speed): _start(start), _end(end), _atr(attr), _state(state), _speed(speed) {}
            Cinematic() = default;
            Position _start;
            Position _end;
            Attributes _atr;
            bool _state;
            int _speed;
            std::string _name = "Cinematic";
            std::string getName() const {
                return _name;
            }
            std::string getInfo() const {
                return _state ? "On" : "Off";
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !CINEMATIC_HPP_ */
