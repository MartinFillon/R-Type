/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** Registry
*/

#include "Registry.hpp"

template <class Component>
ecs::SparseArray<Component> &ecs::Registry::register_component()
{
    auto type = std::type_index(typeid(ecs::SparseArray<Component>));
    if (_componentsArrays.find(type) == _componentsArrays.end()) {
        _componentsArrays[type] = ecs::SparseArray<Component>();
    }
    return std::any_cast<ecs::SparseArray<Component> &>(_componentsArrays[type]);
}

template <class Component>
ecs::SparseArray<Component> &ecs::Registry::get_components()
{
    return std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(SparseArray<Component>))]);
}

template <class Component>
ecs::SparseArray<Component> &ecs::Registry::register_if_not_exist()
{
    auto type = std::type_index(typeid(SparseArray<Component>));
    if (_componentsArrays.find(type) == _componentsArrays.end()) {
        return register_component<Component>();
    }
    return std::any_cast<SparseArray<Component> &>(_componentsArrays[type]);
}

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

template <typename Function>
void ecs::Registry::add_system(Function &&f)
{
    _systems.push_back(f);
}

void ecs::Registry::run_systems()
{
    for (auto &system : _systems) {
        system(*this);
    }
}
