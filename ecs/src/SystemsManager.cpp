/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SystemsManager
*/

#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include <spdlog/spdlog.h>
#include <thread>
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
        std::vector<std::thread> threads;

        for (auto &system : __systems) {
            threads.emplace_back([system, &r, &ctx, &f]() {
                system->operator()(r, ctx, f);
            });
        }

        for (auto &thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

} // namespace ecs::systems
