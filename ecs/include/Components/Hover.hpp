/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hover
*/

#ifndef HOVER_HPP_
#define HOVER_HPP_

namespace ecs {
    namespace component {
        /// @brief Hover Component to know if the entity is Hover, it's stored a boolean to know it
        struct Hover {
            bool _value;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !HOVER_HPP_ */
