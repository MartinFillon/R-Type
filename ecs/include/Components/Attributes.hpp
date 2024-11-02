/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animations
*/

#ifndef ATTRIBUTES_HPP_
#define ATTRIBUTES_HPP_

#include <cstddef>
namespace ecs {
    namespace component {

        struct Attributes {

            enum class EntityType {
                None,
                Background,
                Player,
                Weapon,
                Ennemy,
                Rectangle,
                Planes,
                Sphere
            };

            enum class SecondaryType { None, Basic, Milespates, Boss, First, Second, Killable, Finsih };

            EntityType _entity_type;
            SecondaryType _secondary_type;
            std::size_t _identifyer;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ATTRIBUTES_HPP_ */
