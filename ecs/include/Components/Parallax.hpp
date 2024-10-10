/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Parallax
*/

#ifndef PARALAX_HPP_
#define PARALAX_HPP_

namespace ecs {
    namespace component {
        /// @brief Parallax component for parralax entity, its got a value to know if he is in the screen, a speed and a multiplicator to change the speed with the foreground or the background
        struct Parallax {
            bool _value;
            double _speed;
            int _multiplicator;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !PARALAX_HPP_ */
