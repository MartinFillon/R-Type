/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Life
*/

#ifndef LIFE_HPP_
#define LIFE_HPP_

#include <string>
namespace ecs {
    namespace component {
        struct Life {
            int _life;
            std::string _name = "Life";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !LIFE_HPP_ */
