/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#include <filesystem>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "ComponentFactory.hpp"
#include "Entity.hpp"
#include "Registry.hpp"
#include "nlohmann/detail/value_t.hpp"
#include "nlohmann/json_fwd.hpp"

namespace ecs {
    ComponentFactory::ComponentFactory()
    {
        try {
            std::filesystem::path path = std::filesystem::current_path() / "components";

            for (const auto &entry : std::filesystem::directory_iterator(path)) {
                if (entry.is_regular_file()) {
                    std::string path = entry.path().string();
                    std::string name = entry.path().stem().string().substr(3);
                    registerComponent(name, path);
                }
            }
        } catch (const std::filesystem::__cxx11::filesystem_error &error) {
            spdlog::error("Error on searching path: {}", error.what());
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
        if (!std::filesystem::exists(file)) {
            throw ComponentFactoryException(ERROR_FILE_NOT_FOUND(file));
        }

        nlohmann::json config = nlohmann::json::parse(f);
        if (config == nlohmann::detail::value_t::discarded) {
            throw ComponentFactoryException(ERROR_PARSING_ERROR(file));
        }
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
        if (!std::filesystem::exists(file)) {
            throw ComponentFactoryException(ERROR_FILE_NOT_FOUND(file));
        }

        nlohmann::json config = nlohmann::json::parse(f);
        if (config == nlohmann::detail::value_t::discarded) {
            throw ComponentFactoryException(ERROR_PARSING_ERROR(file));
        }

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
            spdlog::warn("Cannot find: {}", component);
        }
    }
} // namespace ecs
