/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#include <fstream>

#include <nlohmann/json.hpp>

#include "ComponentFactory.hpp"
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
    ComponentFactory::ComponentFactory(Registry &r) : _r(r)
    {
        std::filesystem::path path = std::filesystem::current_path();
    }

    ComponentFactory::~ComponentFactory() {}

    void ComponentFactory::registerComponent(std::string &name, std::string &path)
    {
        // components[name] = DlLoader<void>(path, "register_component");
    }

    Entity ComponentFactory::createEntity(const std::string &file)
    {
        std::ifstream f(getPathToConfig() + file);
        nlohmann::json config = nlohmann::json::parse(f);

        Entity e = _r.spawn_entity();
        _r._entities.addEntity(e.getId());

        for (auto &c : config["active"]) {
            createComponent(e, c, config["components"][c]);
        }
        return e;
    }

    Entity ComponentFactory::createEntity(int id, const std::string &file)
    {
        std::ifstream f(file);
        nlohmann::json config = nlohmann::json::parse(f);

        Entity e = Entity(id);
        _r._entities.addEntity(e.getId());

        for (auto &c : config["active"]) {
            createComponent(e, c, config["components"][c]);
        }
        return e;
    }

    void ComponentFactory::createComponent(const Entity e, const std::string &component, const nlohmann::json &node)
    {
        // if (components.find(component) != components.end()) {
        // components[component].call(std::ref(_r), std::ref(e), std::ref(node));
        // }
    }
} // namespace ecs
