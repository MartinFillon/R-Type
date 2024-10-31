/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Destroyable
*/

#ifndef DESTROYABLE_HPP_
#define DESTROYABLE_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Destroyable : IComponent {
            enum DestroyState { ALIVE, WAITING, DESTROYING, DESTROYED };
            Destroyable(DestroyState state, bool animate): _state(state), _animate(animate) {}
            Destroyable() = default;
            DestroyState _state;
            bool _animate;
            std::string _name = "Destroyable";
            std::string getName() const {
                return _name;
            }

        };
    }; // namespace component
}; // namespace ecs

#endif /* !DESTROYABLE_HPP_ */
