/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** Registry
*/

#include "Registry.hpp"
#include <memory>
#include "ComponentFactory.hpp"
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Parallax.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "IContext.hpp"

ecs::Entity ecs::Registry::spawn_entity()
{
    return Entity(_entityCount++);
}

void ecs::Registry::erase(const std::size_t &entityIdx)
{
    auto &attributes = register_if_not_exist<ecs::component::Attributes>();
    auto &positions = register_if_not_exist<ecs::component::Position>();
    auto &drawable = register_if_not_exist<ecs::component::Drawable>();
    auto &sprite = register_if_not_exist<ecs::component::Sprite>();
    auto &animation = register_if_not_exist<ecs::component::Animations>();
    auto &parallax = register_if_not_exist<ecs::component::Parallax>();
    auto &size = register_if_not_exist<ecs::component::Size>();
    auto &controllable = register_if_not_exist<ecs::component::Controllable>();
    auto &destroyable = register_if_not_exist<ecs::component::Destroyable>();

    attributes.erase(entityIdx);
    destroyable.erase(entityIdx);
    positions.erase(entityIdx);
    drawable.erase(entityIdx);
    sprite.erase(entityIdx);
    animation.erase(entityIdx);
    parallax.erase(entityIdx);
    size.erase(entityIdx);
    controllable.erase(entityIdx);
}

void ecs::Registry::run_systems(ecs::ComponentFactory &f, std::shared_ptr<IContext> ctx = nullptr)
{
    std::shared_ptr<Registry> r = this->shared_from_this();

    _systemsManager->runSystems(r, ctx, f);
}
