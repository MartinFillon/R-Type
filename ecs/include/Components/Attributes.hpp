/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animations
*/

#ifndef ATTRIBUTES_HPP_
#define ATTRIBUTES_HPP_

#include "IComponent.hpp"
#include <unordered_map>
#include <sstream>
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
            std::string getInfo() const {
                std::ostringstream stream;

                std::unordered_map<ecs::component::Attributes::EntityType, std::string> entities_types = {
                    {ecs::component::Attributes::EntityType::Player, "player"},
                    {ecs::component::Attributes::EntityType::Weapon, "weapon"},
                    {ecs::component::Attributes::EntityType::Ennemy, "ennemy"},
                    {ecs::component::Attributes::EntityType::Background, "background"},
                    {ecs::component::Attributes::EntityType::Rectangle, "rectangle"},
                    {ecs::component::Attributes::EntityType::Planes, "planes"},
                };
                std::unordered_map<ecs::component::Attributes::SecondaryType, std::string> ennemies_types = {
                    {ecs::component::Attributes::SecondaryType::None, "none"},
                    {ecs::component::Attributes::SecondaryType::Basic, "basic"},
                    {ecs::component::Attributes::SecondaryType::Milespates, "milepates"},
                    {ecs::component::Attributes::SecondaryType::Boss, "boss"},
                    {ecs::component::Attributes::SecondaryType::First, "first"},
                    {ecs::component::Attributes::SecondaryType::Second, "second"},
                    {ecs::component::Attributes::SecondaryType::Killable, "killable"},
                    {ecs::component::Attributes::SecondaryType::Finsih, "finish"}
                };

                stream << "Type: " << entities_types[_entity_type] << " Secondary Type: " << entities_types[_entity_type];

                return stream.str();
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ATTRIBUTES_HPP_ */
