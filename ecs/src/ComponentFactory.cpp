/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

#include "ComponentFactory.hpp"
#include "ComponentLoader.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

std::string getEnvOrDefault(const std::string &env, const std::string &def)
{
    const char *val = std::getenv(env.c_str());
    return val ? val : def;
}

std::string getPathToConfig()
{
#ifndef RELEASE
    std::string path = "./";
#elif defined(__linux__) || defined(__APPLE__)
    std::string path = getEnvOrDefault("XDG_CONFIG_HOME", "~/.config/");
    path += "r-type/";
#elif defined(_WIN32)
    std::string path = getEnvOrDefault("APPDATA", "./");
    path += "r-type/";
#endif
    return path;
}

namespace ecs {
    ComponentFactory::ComponentFactory()
    {
        std::filesystem::path path = std::filesystem::current_path() / "components";

        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                std::string path = entry.path().string();
                std::string name = entry.path().stem().string();
                registerComponent(name, path);
            }
        }

        std::cerr << "Factory inited" << std::endl;
    }

    ComponentFactory::~ComponentFactory() {}

    void ComponentFactory::registerComponent(std::string &name, std::string &path)
    {
        components[name] = std::make_shared<ComponentLoader>(path);
    }

    Entity ComponentFactory::createEntity(std::shared_ptr<Registry> r, const std::string &file)
    {
        std::ifstream f(getPathToConfig() + file);
        nlohmann::json config = nlohmann::json::parse(f);

        Entity e = r->spawn_entity();
        r->_entities.addEntity(e.getId());

        for (auto &c : config["active"]) {
            createComponent(r, e, c, config["components"][c]);
        }
        return e;
    }

    Entity ComponentFactory::createEntity(std::shared_ptr<Registry> r, int id, const std::string &file)
    {
        std::ifstream f(file);
        nlohmann::json config = nlohmann::json::parse(f);

        Entity e = Entity(id);
        r->_entities.addEntity(e.getId());

        for (auto &c : config["active"]) {
            createComponent(r, e, c, config["components"][c]);
        }
        return e;
    }

    void ComponentFactory::createComponent(
        std::shared_ptr<Registry> r,
        Entity e,
        const std::string &component,
        const nlohmann::json &node
    )
    {
        if (components.find(component) != components.end()) {
            components[component]->call(r, e, node);
        }
    }
} // namespace ecs
