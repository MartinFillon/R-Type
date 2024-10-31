/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** destroyables
*/

#include <nlohmann/json.hpp>

#include "Components/Destroyable.hpp"
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
    auto &destroyables = registry->register_component<ecs::component::Destroyable>();

    destroyables[entity.getId()] =
        ecs::component::Destroyable{ecs::component::Destroyable::DestroyState::ALIVE, component["animate"]};
}
