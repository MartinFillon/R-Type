/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animations
*/

#ifndef ANIMATIONS_HPP_
#define ANIMATIONS_HPP_

#include "Clock.hpp"

namespace ecs {
    /// @brief Component namespaces for components type
    namespace component {
        /// @brief Object is to know what object is in the sparse array and make difference in all Entity
        enum Object { Background, Player, Weapon, Ennemies, InDestroy };

        /// @brief Type is to know wich type this object is, because it can be an Ennemies but wich one ? Basic ? Milespates ? Boss. The Type type is to know to the type of the object
        enum Type { None, Basic, Milespates, Boss };

        /// @brief Animations component to handling the rectangle to set in the image of the texture, it get his clock, width, height, x, y, and a rotation if nedded
        struct Animations {
            ecs::Clock _clock;
            double _width;
            double _height;
            double _x;
            double _y;
            double _rotation;
            Object _object;
            Type _type;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ANIMATIONS_HPP_ */
