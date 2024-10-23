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

#include "Registry.hpp"
#include "SystemsManager.hpp"

namespace ecs::systems {
    SystemsManager::SystemsManager(const std::string config)
    {
        nlohmann::json_schema::json_validator validator;

        std::ifstream file = std::ifstream(config);
        std::ifstream schemafile = std::ifstream("./schema/systems.json");

        const nlohmann::json conf = nlohmann::json::parse(config);
        const nlohmann::json schema = nlohmann::json::parse(schemafile);

        validator.set_root_schema(schema);
        validator.validate(conf);

        for (auto &system : conf["systems"]) {
            add_system(system);
        }
    }

    SystemsManager::~SystemsManager() {}

    void SystemsManager::add_system(const std::string name)
    {
        std::string path = std::filesystem::current_path() / "systems" / ("lib" + name + ".so");

        std::cerr << "Loading system: " << path << std::endl;
    }

    void SystemsManager::runSystems(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> &ctx, ComponentFactory &f)
    {
        for (auto &system : __systems) {
            system->operator()(r, ctx, f);
        }
    }

} // namespace ecs::systems
