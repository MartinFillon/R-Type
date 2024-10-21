/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** Registry
*/

#include "Registry.hpp"
#include <memory>
#include "ComponentFactory.hpp"
#include "IContext.hpp"

ecs::Entity ecs::Registry::spawn_entity()
{
    return Entity(_entityCount++);
}

void ecs::Registry::erase(const std::size_t &entityIdx)
{
    auto &positions = register_component<ecs::component::Position>();
    auto &drawable = register_component<ecs::component::Drawable>();
    auto &sprite = register_component<ecs::component::Sprite>();
    auto &animation = register_component<ecs::component::Animations>();
    auto &parallax = register_component<ecs::component::Parallax>();
    auto &size = register_component<ecs::component::Size>();
    auto &controllable = register_component<ecs::component::Controllable>();
    auto &destroyable = register_component<ecs::component::Destroyable>();

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
    std::shared_ptr<Registry> r = std::make_shared<Registry>(*this);
    for (auto &system : _systems) {
        system(r, ctx, f);
    }
}
