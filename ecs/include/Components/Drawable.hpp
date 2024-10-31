/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct Drawable {
            bool _drawable;
            std::string _name = "Drawable";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !DRAWABLE_HPP_ */
