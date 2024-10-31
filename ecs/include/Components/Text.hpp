/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <string>
#include "Components/IComponent.hpp"

namespace ecs {
    namespace component {
        struct Text : public IComponent {
            Text(std::string text): _string(text) {}
            Text() = default;
            std::string _string;
            std::string _name = "Text";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !TEXT_HPP_ */
