/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Drawable : public IComponent {
            Drawable(bool drawable): _drawable(drawable) {}
            Drawable() = default;
            bool _drawable;
            std::string _name = "Drawable";
            std::string getName() const {
                return _name;
            }
            std::string getInfo() const {
                return std::string("State: " + std::string(_drawable ? "true" : "false"));
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !DRAWABLE_HPP_ */
