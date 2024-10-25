/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** cinematics
*/

#include <nlohmann/json.hpp>

#include "Components/Attributes.hpp"
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
    ecs::component::Attributes::EntityType entity_type = ecs::component::Attributes::EntityType::None;
    ecs::component::Attributes::EnnemyType ennemy_type = ecs::component::Attributes::EnnemyType::None;
    ecs::component::Position startPos{0, 0, false};
    ecs::component::Position endPos{0, 0, false};
    ecs::component::Attributes atr;
    startPos._x = component["xStart"];
    startPos._y = component["yStart"];

    endPos._x = component["xEnd"];
    endPos._y = component["yEnd"];

    if (component["objectType"] == "background") {
        entity_type = ecs::component::Attributes::EntityType::Background;
    }
    if (component["objectType"] == "player") {
        entity_type = ecs::component::Attributes::EntityType::Player;
    }
    if (component["objectType"] == "weapon") {
        entity_type = ecs::component::Attributes::EntityType::Weapon;
    }
    if (component["objectType"] == "ennemies") {
        entity_type = ecs::component::Attributes::EntityType::Ennemy;
    }

    if (component["type"] == "basic") {
        ennemy_type = ecs::component::Attributes::EnnemyType::Basic;
    }
    if (component["type"] == "milespates") {
        ennemy_type = ecs::component::Attributes::EnnemyType::Milespates;
    }
    if (component["type"] == "boss") {
        ennemy_type = ecs::component::Attributes::EnnemyType::Boss;
    }
    if (component["type"] == "first") {
        ennemy_type = ecs::component::Attributes::EnnemyType::First;
    }
    if (component["type"] == "second") {
        ennemy_type = ecs::component::Attributes::EnnemyType::Second;
    }

    atr._entity_type = entity_type;
    atr._ennemy_type = ennemy_type;

    bool state = component["state"];
    int speed = component["speed"];

    cinematics[entity.getId()] = ecs::component::Cinematic{startPos, endPos, atr, state, speed };
}
