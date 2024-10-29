/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** animations
*/

#include <nlohmann/json.hpp>

#include "Components/Animations.hpp"
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
    auto &animations = registry->register_component<ecs::component::Animations>();

    animations[entity.getId()] = ecs::component::Animations{
        ecs::Clock(), component["width"], component["height"], component["x"], component["y"], component["rotation"]
    };
}
