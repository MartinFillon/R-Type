/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include <any>
#include <functional>
#include <typeindex>
#include <vector>
#include <unordered_map>

#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Parallax.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "SparseArray.hpp"

namespace ecs {
    class Registry {
      public:
        template <class Component>
        SparseArray<Component> &register_component()
        {
            auto type = std::type_index(typeid(SparseArray<Component>));
            if (_componentsArrays.find(type) == _componentsArrays.end()) {
                _componentsArrays[type] = SparseArray<Component>();
            }
            return std::any_cast<SparseArray<Component> &>(_componentsArrays[type]);
        }

        template <class Component>
        SparseArray<Component> &get_components()
        {
            return std::any_cast<SparseArray<Component> &>(
                _componentsArrays[std::type_index(typeid(SparseArray<Component>))]
            );
        }

        template <class Component>
        SparseArray<Component> &register_if_not_exist()
        {
            auto type = std::type_index(typeid(SparseArray<Component>));
            if (_componentsArrays.find(type) == _componentsArrays.end()) {
                return register_component<Component>();
            }
            return std::any_cast<SparseArray<Component> &>(_componentsArrays[type]);
        }

        Entity spawn_entity()
        {
            
            return Entity(_entityCount++);
        }

        void erase(const std::size_t &entityIdx)
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
        void add_system(Function &&f)
        {
            _systems.push_back(f);
        }

        void run_systems()
        {
            for (auto &system : _systems) {
                system(*this);
            }
        }

        EntityManager _entities;

      private:
        std::vector<std::function<void(Registry &)>> _systems;
        std::unordered_map<std::type_index, std::any> _componentsArrays;
        std::size_t _entityCount = 0;
    };
} // namespace ecs

#endif /* !REGISTRY_HPP_ */
