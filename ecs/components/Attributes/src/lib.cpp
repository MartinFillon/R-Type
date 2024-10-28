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

#if defined(_WIN32) || defined(_WIN64)
    #define LIB_EXPORT __declspec(dllexport)
#else
    #define LIB_EXPORT
#endif

extern "C" LIB_EXPORT void register_component(
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
        {"rectangle", ecs::component::Attributes::EntityType::Rectangle},
    };
    std::unordered_map<std::string, ecs::component::Attributes::SecondaryType> ennemies_types = {
        {"none", ecs::component::Attributes::SecondaryType::None},
        {"basic", ecs::component::Attributes::SecondaryType::Basic},
        {"milepates", ecs::component::Attributes::SecondaryType::Milespates},
        {"boss", ecs::component::Attributes::SecondaryType::Boss},
        {"first", ecs::component::Attributes::SecondaryType::First},
        {"second", ecs::component::Attributes::SecondaryType::Second},
    };

    attributes[entity.getId()] = ecs::component::Attributes{
        entities_types[component["entityType"]], ennemies_types[component["secondaryType"]], entity.getId()
    };
}
