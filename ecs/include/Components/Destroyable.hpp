/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Destroyable
*/

#ifndef DESTROYABLE_HPP_
#define DESTROYABLE_HPP_

#include <sstream>
#include <string>
#include "IComponent.hpp"
#include <unordered_map>

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
            std::string getInfo() const {
                std::ostringstream stream;
                std::unordered_map<DestroyState, std::string> state = {
                    {ALIVE, "Alive"},
                    {WAITING, "Waiting"},
                    {DESTROYING, "Destroying"},
                    {DESTROYED, "Destroyed"}
                };

                stream << "Animate: " << std::string(_animate ? "true" : "false") << " State: " << state[_state];

                return stream.str();
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !DESTROYABLE_HPP_ */
