/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SystemsManager
*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include "Registry.hpp"
#include "SystemsManager.hpp"

namespace ecs::systems {
    void SystemsManager::AddSystem(std::shared_ptr<ISystems> &system)
    {
        __systems.push_back(system);
    }

    void SystemsManager::AddSystem(ISystems *system)
    {
        __systems.push_back(std::shared_ptr<ISystems>(system));
    }

    void SystemsManager::runSystems(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> &ctx, ComponentFactory &f)
    {
        for (auto &system : __systems) {
            system->operator()(r, ctx, f);
        }
    }

} // namespace ecs::systems
