/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Destroyable
*/

#ifndef DESTROYABLE_HPP_
#define DESTROYABLE_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct Destroyable {
            enum DestroyState { ALIVE, WAITING, DESTROYING, DESTROYED };

            DestroyState _state;
            bool _animate;
            std::string _name = "Destroyable";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !DESTROYABLE_HPP_ */
