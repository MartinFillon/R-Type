/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** Registry
*/

#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include "Registry.hpp"
#include "ComponentFactory.hpp"
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/IComponent.hpp"
#include "Components/Parallax.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "IContext.hpp"
#include "SparseArray.hpp"

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
    std::ofstream stream("debug.log");
    std::shared_ptr<Registry> r = this->shared_from_this();

    _systemsManager->runSystems(r, ctx, f);
    if (_debugMode) {
        stream << "| Entities ";
        std::vector<std::string> names = get_all_component_names();

        std::string temp;
        for (auto &i: names) {
            if (i == temp) {
                continue;
            }
            stream << "| " << i << "    ";
            temp = i;
        }

        for (std::size_t idx = 0; idx < _entityCount; ++idx) {
            stream << "|     " << idx << "    ";
            std::string tempTwo;
            for (const auto &component : _componentList) {
                if (tempTwo == component->getName()) {
                    continue;
                }
                stream << "| " << component->getName() << "    ";
                tempTwo = component->getName();
            }
            stream << "\n";
        }
        stream.close();
        exit(1);
    }
}
