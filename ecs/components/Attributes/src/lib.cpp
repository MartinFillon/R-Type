/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** attributes
*/

#include <nlohmann/json.hpp>

#include "Components/Attributes.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &attributes = registry->register_component<ecs::component::Attributes>();

    std::unordered_map<std::string, ecs::component::Attributes::EntityType> entities_types = {
        {"player", ecs::component::Attributes::EntityType::Player},
        {"weapon", ecs::component::Attributes::EntityType::Weapon},
        {"ennemy", ecs::component::Attributes::EntityType::Ennemy},
        {"background", ecs::component::Attributes::EntityType::Background},
    };
    std::unordered_map<std::string, ecs::component::Attributes::SecondaryType> ennemies_types = {
        {"none", ecs::component::Attributes::SecondaryType::None},
        {"basic", ecs::component::Attributes::SecondaryType::Basic},
        {"milepates", ecs::component::Attributes::SecondaryType::Milespates},
        {"boss", ecs::component::Attributes::SecondaryType::Boss},
        {"first", ecs::component::Attributes::SecondaryType::First},
        {"second", ecs::component::Attributes::SecondaryType::Second},
    };

    if (entities_types[component["entityType"]] == ecs::component::Attributes::EntityType::Ennemy ||
        entities_types[component["entityType"]] == ecs::component::Attributes::EntityType::Weapon) {
        attributes[entity.getId()] = ecs::component::Attributes{
            entities_types[component["entityType"]], ennemies_types[component["ennemyType"]], entity.getId()
        };
    } else {
        attributes[entity.getId()] = ecs::component::Attributes{
            entities_types[component["entityType"]], ecs::component::Attributes::SecondaryType::None, entity.getId()
        };
    }
}
