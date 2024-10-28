/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** animations
*/

#include <nlohmann/json.hpp>

#include "Components/KeyPressed.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &components = registry->register_component<ecs::component::KeyPressed>();
    ecs::component::Key value = ecs::component::Key::NoneKey;

    if (component == "up") {
        value = ecs::component::Key::Up;
    }

    if (component == "down") {
        value = ecs::component::Key::Down;
    }

    if (component == "right") {
        value = ecs::component::Key::Right;
    }

    if (component == "left") {
        value = ecs::component::Key::Left;
    }

    if (component == "punch") {
        value = ecs::component::Key::Punch;
    }

    if (component == "kick") {
        value = ecs::component::Key::Kick;
    }

    components[entity.getId()] = {value};
}
