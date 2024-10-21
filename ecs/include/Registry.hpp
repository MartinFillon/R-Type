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
#include <memory>
#include <typeindex>
#include <vector>
#include <unordered_map>

#include "ComponentFactory.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "IContext.hpp"
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

        template <typename Function>
        void add_system(Function &&f)
        {
            _systems.push_back(f);
        }

        Entity spawn_entity();
        void erase(const std::size_t &entityIdx);
        void run_systems(ComponentFactory &f, std::shared_ptr<IContext> ctx);

        EntityManager _entities;

        Registry() {}

        Registry(Registry &r)
        {
            _systems = r._systems;
            _componentsArrays = r._componentsArrays;
            _entityCount = r._entityCount;
        }

      private:
        std::vector<
            std::function<void(std::shared_ptr<Registry> &, std::shared_ptr<ecs::IContext>, ComponentFactory &r)>>
            _systems;
        std::unordered_map<std::type_index, std::any> _componentsArrays;
        std::size_t _entityCount = 0;
    };
} // namespace ecs

#endif /* !REGISTRY_HPP_ */
