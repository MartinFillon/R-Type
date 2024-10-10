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
    /// @brief Registry is the class that handle all the SparseArray, Systems and Entity size
    class Registry {
      public:
        /// @brief this method is to register a SparseArray of the template Component, if it's alreadey exists it's juste reassign it
        /// @tparam Component is the template of a component, in the component Folder, it is always a structure
        /// @return a reference of the registered component
        template <class Component>
        SparseArray<Component> &register_component()
        {
            auto type = std::type_index(typeid(SparseArray<Component>));
            if (_componentsArrays.find(type) == _componentsArrays.end()) {
                _componentsArrays[type] = SparseArray<Component>();
            }
            return std::any_cast<SparseArray<Component> &>(_componentsArrays[type]);
        }

        /// @brief this method let us get a get a a SparseArray of the template Component
        /// @tparam Component is the template of a component, in the component Folder, it is always a structure
        /// @return a reference to the SparseArray of the component
        template <class Component>
        SparseArray<Component> &get_components()
        {
            return std::any_cast<SparseArray<Component> &>(
                _componentsArrays[std::type_index(typeid(SparseArray<Component>))]
            );
        }

        /// @brief this method is to register a SparseArray of the template Component, if it's alreadey exists it's juste reassign it
        /// @tparam Component is the template of a component, in the component Folder, it is always a structure
        /// @return a reference of the registered component

        template <class Component>
        SparseArray<Component> &register_if_not_exist()
        {
            auto type = std::type_index(typeid(SparseArray<Component>));
            if (_componentsArrays.find(type) == _componentsArrays.end()) {
                return register_component<Component>();
            }
            return std::any_cast<SparseArray<Component> &>(_componentsArrays[type]);
        }

        /// @brief spawn_entity method let us get a new Entity, it create a new entity index
        /// @return the new Entity
        Entity spawn_entity()
        {
            return Entity(_entityCount++);
        }

        /// @brief erase method erase an entity in all sparseArray, it call all the SparseArray registered and erase the entity in all
        /// @param entityIdx is the Entity Id
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

        /// @brief add_system method add a system to his std::vector of system
        /// @tparam Function is a template for function to say that it is a function
        /// @param f is an rvalue of a function in other words a system wich is a class that must avec an operator()(Registry &)
        template <typename Function>
        void add_system(Function &&f)
        {
            _systems.push_back(f);
        }

        /// @brief run_systems method run all the systemsthat is stored
        void run_systems()
        {
            for (auto &system : _systems) {
                system(*this);
            }
        }

        /// @brief EntityManager is the manager of all entity, it's an encapsulation of std::vector<std::size_t> to handle all index in other words all the Entity
        EntityManager _entities;

      private:
        /// @brief _systems is a private member of Registry, it is a vector of all function, all systems that have been added, a system must avec an operator()(Registry &)
        std::vector<std::function<void(Registry &)>> _systems;
        /// @brief _componentsArray is an unordered map of type_index and std::any, it's stored the id in key that is generated by type index and it's value is a SparseArray of a component that is unique, as the key because the id of the key is generated in function of the SparseArray of a component
        std::unordered_map<std::type_index, std::any> _componentsArrays;
        /// @brief handle the size of the entity stored
        std::size_t _entityCount = 0;
    };
} // namespace ecs

#endif /* !REGISTRY_HPP_ */
