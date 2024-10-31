/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Planes
*/

#ifndef PLANES_HPP_
#define PLANES_HPP_

#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Planes : public IComponent {
            Planes(int lenght, int width): _lenght(lenght), _width(width) {}
            Planes() = default;
            int _lenght;
            int _width;
            std::string _name = "Planes";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !PLANES_HPP_ */
