/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** Registry
*/

#include <fstream>
#include <ios>
#include <memory>
#include <string>
#include <typeindex>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Registry.hpp"
#include "ComponentFactory.hpp"
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
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
    std::ofstream stream("debug.log", std::ios_base::app);
    std::shared_ptr<Registry> r = this->shared_from_this();

    _systemsManager->runSystems(r, ctx, f);

    if (_debugMode) {
        // debug();
        std::vector<std::string> names = get_all_component_names();
        std::vector<size_t> colWidths(names.size() + 1, 0);

        colWidths[0] = std::max(colWidths[0], std::string("Entities").length());
        for (size_t i = 0; i < names.size(); ++i) {
            colWidths[i + 1] = std::max(colWidths[i + 1], names[i].length());
        }

        for (std::size_t idx = 0; idx < _entityCount; ++idx) {
            colWidths[0] = std::max(colWidths[0], std::to_string(idx).length());

            size_t compIndex = 1;
            for (const auto &[_, component] : _componentList) {
                std::type_index type = std::type_index(typeid(component.get()));
                size_t infoLength = component->getInfo().length();
                colWidths[compIndex] = std::max(colWidths[compIndex], infoLength);
                ++compIndex;
            }
        }

        stream << "| " << std::setw(colWidths[0]) << std::left << "Entities" << " ";
        for (size_t i = 0; i < names.size(); ++i) {
            stream << "| " << std::setw(colWidths[i + 1]) << std::left << names[i] << " ";
        }
        stream << "\n";

        for (std::size_t idx = 0; idx < _entityCount; ++idx) {
            stream << "| " << std::setw(colWidths[0]) << idx << " ";

            size_t compIndex = 1;
            for (const auto &[_, component] : _componentList) {
                stream << "| " << std::setw(colWidths[compIndex]) << component->getInfo() << " ";
                ++compIndex;
            }
            stream << "\n";
        }

        stream.close();
    }

}
