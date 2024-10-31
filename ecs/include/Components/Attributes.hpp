/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animations
*/

#ifndef ATTRIBUTES_HPP_
#define ATTRIBUTES_HPP_

#include "IComponent.hpp"
#include <string>

namespace ecs {
    namespace component {

        struct Attributes : public IComponent {

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
            Attributes() = default;
            Attributes(EntityType firstType, SecondaryType secondaryType, std::size_t identifyer): _entity_type(firstType), _secondary_type(secondaryType), _identifyer(identifyer) {}
            Attributes(EntityType firstType, SecondaryType secondaryType): _entity_type(firstType), _secondary_type(secondaryType), _identifyer(0) {}
            EntityType _entity_type;
            SecondaryType _secondary_type;
            std::size_t _identifyer;
            std::string _name = "Attributes";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ATTRIBUTES_HPP_ */
