/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Life
*/

#ifndef LIFE_HPP_
#define LIFE_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Life : public IComponent {
            Life(int life): _life(life) {}
            Life() = default;
            int _life;
            std::string _name = "Life";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !LIFE_HPP_ */
