/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Destroyable
*/

#ifndef DESTROYABLE_HPP_
#define DESTROYABLE_HPP_

namespace ecs {
    namespace component {
        /// @brief Destroyable component only store a boolean to know if the entity is destroyable or not
        struct Destroyable {
            bool _destroyable;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !DESTROYABLE_HPP_ */
