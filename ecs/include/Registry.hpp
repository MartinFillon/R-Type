/*
** EPITECH PROJECT, 2024
** RtypeBootstrap
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
    #define REGISTRY_HPP_

#include <typeindex>
#include <unordered_map>
#include <functional>
#include <any>
#include "./Entity.hpp"
#include "./SparseArray.hpp"


namespace ecs {
    class Registry {
        public:
            template <class Component>
            SparseArray<Component> &register_component() {
                auto type = std::type_index(typeid(SparseArray<Component>));
                if (_componentsArrays.find(type) == _componentsArrays.end()) {
                    _componentsArrays[type] = SparseArray<Component>();
                }
                return std::any_cast<SparseArray<Component>&>(_componentsArrays[type]);
            }

            template <class Component>
            SparseArray<Component> &get_components() {
                return std::any_cast<SparseArray<Component>&>(_componentsArrays[std::type_index(typeid(SparseArray<Component>))]);
            }

            Entity spawn_entity() {
                return Entity(_entityCount++);
            }

            void remove_component(Entity const &from) {
                std::size_t idx = 0;

                for (const auto &i: _componentsArrays) {
                    if (from.getId() == idx) {
                        _componentsArrays.erase(i.first);
                        break;
                    }
                    idx += 1;
                }
            }

            template <typename Function>
            void add_system(Function &&f) {
                _systems.push_back(f);
            }

            void run_systems() {
                for (auto &system: _systems) {
                    system(*this);
                }
            }

        private:
            std::vector<std::function<void(Registry &)>> _systems;
            std::unordered_map<std::type_index, std::any> _componentsArrays;
            std::size_t _entityCount = 0;
    };
}

#endif /* !REGISTRY_HPP_ */
