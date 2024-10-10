/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

namespace ecs {
    namespace component {
        struct Drawable {
        /// @brief Drawable component only store a boolean to know if the entity is drawable or not
            bool _drawable;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !DRAWABLE_HPP_ */
