/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct IComponent {
            virtual ~IComponent() = default;
            virtual std::string getName() const = 0;
            virtual std::string getInfo() const = 0;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ICOMPONENT_HPP_ */
