/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Controllable
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

namespace ecs {
    namespace component {
        /// @brief Controllable component to know if the component is controllable by the player and his speed, this component is applicable to all component because they're speed is store in it
        struct Controllable {
            bool _controllable;
            double _speed;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !CONTROLLABLE_HPP_ */
