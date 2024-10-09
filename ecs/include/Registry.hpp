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
        SparseArray<Component> &register_component();

        template <class Component>
        SparseArray<Component> &get_components();

        template <class Component>
        SparseArray<Component> &register_if_not_exist();

        template <typename Function>
        void add_system(Function &&f);

        Entity spawn_entity();
        void erase(const std::size_t &entityIdx);
        void run_systems();

        EntityManager _entities;

      private:
        std::vector<std::function<void(Registry &)>> _systems;
        std::unordered_map<std::type_index, std::any> _componentsArrays;
        std::size_t _entityCount = 0;
    };
} // namespace ecs

#endif /* !REGISTRY_HPP_ */
