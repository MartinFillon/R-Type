/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include <any>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Entity.hpp"
#include "EntityManager.hpp"
#include "IContext.hpp"
#include "SparseArray.hpp"
#include "SystemsManager.hpp"

namespace ecs {
    class ComponentFactory;

    class Registry : public std::enable_shared_from_this<Registry> {
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

        template <typename System>
        void add_system(std::string file)
        {
            _systemsManager->AddSystem<System>(file);
        }

        template <typename System>
        void add_system()
        {
            _systemsManager->AddSystem<System>();
        }

        Entity spawn_entity();
        void erase(const std::size_t &entityIdx);
        void run_systems(ComponentFactory &f, std::shared_ptr<IContext> ctx);

        EntityManager _entities;

        Registry() {}

        Registry(Registry &r)
        {
            _systemsManager = r._systemsManager;
            _componentsArrays = r._componentsArrays;
            _entityCount = r._entityCount;
        }

      private:
        std::shared_ptr<systems::SystemsManager> _systemsManager;
        std::unordered_map<std::type_index, std::any> _componentsArrays;
        std::size_t _entityCount = 0;
    };
} // namespace ecs

#endif /* !REGISTRY_HPP_ */
