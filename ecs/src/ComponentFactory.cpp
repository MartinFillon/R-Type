/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

#include "ComponentFactory.hpp"
#include "Entity.hpp"
#include "Registry.hpp"
#include "nlohmann/json_fwd.hpp"

namespace ecs {
    ComponentFactory::ComponentFactory()
    {
        std::filesystem::path path = std::filesystem::current_path() / "components";

        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                std::string path = entry.path().string();
                std::string name = entry.path().stem().string().substr(3);
                registerComponent(name, path);
            }
        }
    }

    ComponentFactory::~ComponentFactory() {}

    void ComponentFactory::registerComponent(std::string &name, std::string &path)
    {
        components[name] = std::make_shared<ComponentLoader>(path, "register_component");
    }

    Entity ComponentFactory::createEntity(std::shared_ptr<Registry> r, const std::string &file)
    {
        std::ifstream f(file);
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
        } else {
            std::cerr << "Cannot find: " << component << std::endl;
        }
    }
} // namespace ecs
