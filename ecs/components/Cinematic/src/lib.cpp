/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** cinematics
*/

#include <nlohmann/json.hpp>

#include "Components/Animations.hpp"
#include "Components/Cinematic.hpp"
#include "Components/Position.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &cinematics = registry->register_component<ecs::component::Cinematic>();
    ecs::component::Object objectType = ecs::component::Object::InDestroy;
    ecs::component::Type type = ecs::component::Type::None;
    ecs::component::Position startPos{0, 0, false};
    ecs::component::Position endPos{0, 0, false};
    ecs::component::Animations anim;
    startPos._x = component["xStart"];
    startPos._y = component["yStart"];

    endPos._x = component["xEnd"];
    endPos._y = component["yEnd"];

    if (component["objectType"] == "background") {
        objectType = ecs::component::Object::Background;
    }
    if (component["objectType"] == "player") {
        objectType = ecs::component::Object::Player;
    }
    if (component["objectType"] == "weapon") {
        objectType = ecs::component::Object::Weapon;
    }
    if (component["objectType"] == "ennemies") {
        objectType = ecs::component::Object::Ennemies;
    }

    if (component["type"] == "basic") {
        type = ecs::component::Type::Basic;
    }
    if (component["type"] == "milespates") {
        type = ecs::component::Type::Milespates;
    }
    if (component["type"] == "boss") {
        type = ecs::component::Type::Boss;
    }
    if (component["type"] == "first") {
        type = ecs::component::Type::First;
    }
    if (component["type"] == "second") {
        type = ecs::component::Type::Second;
    }

    anim._object = objectType;
    anim._type = type;
    bool state = component["state"];
    int speed = component["speed"];

    cinematics[entity.getId()] = ecs::component::Cinematic{startPos, endPos, anim, state, speed };
}
