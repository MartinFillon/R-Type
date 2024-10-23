/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SystemsManager
*/

#include <algorithm>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>

#include "Systems/ISystems.hpp"
#include "SystemsManager.hpp"

static const nlohmann::json schema = R"({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "name": "a system",
    "properties": {
        "name": {
            "description": "the system name",
            "type": "string"
        }
    }
})"_json;

namespace ecs::systems {
    SystemsManager::SystemsManager(const std::string config)
    {
        std::ifstream file = std::ifstream(config);

        const nlohmann::json conf = nlohmann::json::parse(config);
    }

    SystemsManager::~SystemsManager() {}

    void SystemsManager::runSystems(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> &ctx, ComponentFactory &f)
    {
        std::for_each(__systems.cbegin(), __systems.cend(), [&r, &ctx, &f](std::shared_ptr<ISystems> &item) {
            item->operator()(r, ctx, f);
        });
    }

} // namespace ecs::systems
