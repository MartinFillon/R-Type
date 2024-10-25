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
    std::unordered_map<std::string, ecs::component::Attributes::EnnemyType> ennemies_types = {
        {"none", ecs::component::Attributes::EnnemyType::None},
        {"basic", ecs::component::Attributes::EnnemyType::Basic},
        {"milepates", ecs::component::Attributes::EnnemyType::Milespates},
        {"boss", ecs::component::Attributes::EnnemyType::Boss},
        {"first", ecs::component::Attributes::EnnemyType::First},
        {"second", ecs::component::Attributes::EnnemyType::Second},
    };

    if (entities_types[component["entityType"]] == ecs::component::Attributes::EntityType::Ennemy ||
        entities_types[component["entityType"]] == ecs::component::Attributes::EntityType::Weapon) {
        attributes[entity.getId()] = ecs::component::Attributes{
            entities_types[component["entityType"]], ennemies_types[component["ennemyType"]]
        };
    } else {
        attributes[entity.getId()] = ecs::component::Attributes{
            entities_types[component["entityType"]], ecs::component::Attributes::EnnemyType::None
        };
    }
}
