/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Position
*/

#include <nlohmann/json.hpp>
#include "Components/Sprite.hpp"
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
    auto &components = registry->register_component<ecs::component::Sprite>();
    components[entity.getId()] = ecs::component::Sprite{component};
}
