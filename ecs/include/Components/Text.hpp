/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct Text {
            std::string _string;
            std::string _name = "Text";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !TEXT_HPP_ */
