/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Position
*/

#include <nlohmann/json.hpp>
#include <string>

#include "Components/Animations3D.hpp"
#include "Entity.hpp"
#include "Registry.hpp"
#include <unordered_map>

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &animation = registry->register_component<ecs::component::Animations3D>();

    std::unordered_map<std::string, ecs::component::AnimationType> typeMap = {
        {"dance", ecs::component::AnimationType::DanceAnimation},
        {"die", ecs::component::AnimationType::DieAnimation},
        {"run", ecs::component::AnimationType::RunAnimation},
        {"walk", ecs::component::AnimationType::WalkAnimation},
        {"jump", ecs::component::AnimationType::JumpAnimation}
    };

    std::string path = component["path"];
    bool state = component["state"];
    ecs::component::AnimationType type = typeMap[component["type"]];
    int animCount = component["animCount"];
    int animFrameCounter = component["animFrameCounter"];

    animation[entity.getId()] = {path, state, type, animCount, animFrameCounter};
}
