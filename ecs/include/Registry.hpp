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
#include <string>
#include <typeindex>
#include <unordered_map>

#include "Components/Attributes.hpp"
#include "Components/Cinematic.hpp"
#include "Components/Color.hpp"
#include "Components/Controllable.hpp"
#include "Components/IComponent.hpp"
#include "Components/Velocity.hpp"
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
            auto componentPtr = std::make_shared<Component>();
            if (_componentList.find(type) == _componentList.end()) {
                _componentList[type] = componentPtr;
            }

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
            std::type_index type = std::type_index(typeid(SparseArray<Component>));

            auto componentPtr = std::make_shared<Component>();
            if (_componentList.find(type) == _componentList.end()) {
                _componentList[type] = componentPtr;
            }

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

        std::vector<std::string> get_all_component_names() const
        {
            std::vector<std::string> componentNames;
            for (const auto &[_, component] : _componentList) {
                componentNames.push_back(component->getName());
            }
            return componentNames;
        }

        Entity spawn_entity();
        void erase(const std::size_t &entityIdx);
        void run_systems(ComponentFactory &f, std::shared_ptr<IContext> ctx);

        EntityManager _entities;

        Registry(): _debugMode(false) {}

        Registry(bool debugMode): _debugMode(debugMode) {}

        Registry(Registry &r)
        {
            _systemsManager = r._systemsManager;
            _componentsArrays = r._componentsArrays;
            _entityCount = r._entityCount;
            _debugMode = r._debugMode;
            _componentList = r._componentList;
        }

      private:
        std::shared_ptr<systems::SystemsManager> _systemsManager = std::make_shared<systems::SystemsManager>();
        std::unordered_map<std::type_index, std::any> _componentsArrays;
        std::size_t _entityCount = 0;
        bool _debugMode;
        std::unordered_map<std::type_index, std::shared_ptr<component::IComponent>> _componentList;
    };
} // namespace ecs

#endif /* !REGISTRY_HPP_ */
