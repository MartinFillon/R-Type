/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animations
*/

#ifndef ATTRIBUTES_HPP_
#define ATTRIBUTES_HPP_

namespace ecs {
    namespace component {

        struct Attributes {

            enum class EntityType {
                None,
                Background,
                Player,
                Weapon,
                Ennemy,
            };

            enum class EnnemyType { None, Basic, Milespates, Boss, First, Second };

            EntityType _entity_type;
            EnnemyType _ennemy_type;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ATTRIBUTES_HPP_ */
