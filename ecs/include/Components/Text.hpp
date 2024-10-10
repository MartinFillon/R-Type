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
        /// @brief Text Component, stored the text of the entity as a string
        struct Text {
            std::string _string;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !TEXT_HPP_ */
