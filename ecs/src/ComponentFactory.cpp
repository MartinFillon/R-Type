/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#include <SFML/System/Clock.hpp>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>

#include <nlohmann/json.hpp>

#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Drawable.hpp"
#include "Components/Parallax.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Registry.hpp"

namespace ecs {
    ComponentFactory::ComponentFactory(std::shared_ptr<Registry> &r) : _r(r)
    {
        functions["position"] = [this](const Entity e, const nlohmann::json &node) {
            createPositionComponent(e, node);
        };
        functions["drawable"] = [this](const Entity e, const nlohmann::json &node) {
            createDrawableComponent(e, node);
        };
        functions["sprite"] = [this](const Entity e, const nlohmann::json &node) { createSpriteComponent(e, node); };
        functions["animations"] = [this](const Entity e, const nlohmann::json &node) {
            createAnimationsComponent(e, node);
        };
        functions["parallax"] = [this](const Entity e, const nlohmann::json &node) {
            createParallaxComponent(e, node);
        };
        functions["size"] = [this](const Entity e, const nlohmann::json &node) { createSizeComponent(e, node); };
    }

    ComponentFactory::~ComponentFactory() {}

    void ComponentFactory::createEntity(const std::string &file)
    {
        std::ifstream f(file);
        nlohmann::json config = nlohmann::json::parse(f);

        std::cout << "Creating entity: " << config["name"] << std::endl;
        Entity e = _r->spawn_entity();

        std::cout << "Creating components..." << std::endl;
        for (auto &c : config["active"]) {
            std::cout << "Creating component: " << c << std::endl;
            std::cout << "Creating component: " << config["components"][c] << std::endl;
            createComponent(e, c, config["components"][c]);
        }
        // std::cout << components.Type() << std::endl;
    }

    void ComponentFactory::createComponent(const Entity e, const std::string &name, const nlohmann::json &node)
    {
        functions[name](e, node);
    }

    void ComponentFactory::createPositionComponent(const Entity e, const nlohmann::json &node)
    {
        auto pos_array = _r->register_if_not_exist<component::Position>();

        pos_array[e.getId()] = component::Position{node["x"], node["y"]};
        std::cout << "Position component created with x: " << pos_array[e.getId()]->_x
                  << " y: " << pos_array[e.getId()]->_y << std::endl;
    }

    void ComponentFactory::createDrawableComponent(const Entity e, const nlohmann::json &node)
    {
        auto drawable_array = _r->register_if_not_exist<component::Drawable>();

        drawable_array[e.getId()] = component::Drawable{node};
        std::cout << "Drawable component created with texture: " << drawable_array[e.getId()]->_drawable << std::endl;
    }

    void ComponentFactory::createSpriteComponent(const Entity e, const nlohmann::json &node)
    {
        auto sprite_array = _r->register_if_not_exist<component::Sprite>();

        sprite_array[e.getId()] = component::Sprite{node};
        std::cout << "Sprite component created with texture: " << sprite_array[e.getId()]->_pathToSprite << std::endl;
    }

    void ComponentFactory::createAnimationsComponent(const Entity e, const nlohmann::json &node)
    {
        auto animations_array = _r->register_if_not_exist<component::Animations>();

        animations_array[e.getId()] =
            component::Animations{sf::Clock(), node["width"], node["height"], node["x"], node["y"]};
        std::cout << "Animations component created with width: " << animations_array[e.getId()]->_width
                  << " height: " << animations_array[e.getId()]->_height
                  << " Starting at texture postition x: " << animations_array[e.getId()]->_x
                  << " y: " << animations_array[e.getId()]->_y << std::endl;
    }

    void ComponentFactory::createParallaxComponent(const Entity e, const nlohmann::json &node)
    {
        auto parallax_array = _r->register_if_not_exist<component::Parallax>();
    }

    void ComponentFactory::createSizeComponent(const Entity e, const nlohmann::json &node)
    {
        auto size_array = _r->register_if_not_exist<component::Size>();

        size_array[e.getId()] = component::Size{node["width"], node["height"]};
        std::cout << "Size component created with width: " << size_array[e.getId()]->_width
                  << " height: " << size_array[e.getId()]->_height << std::endl;
    }
} // namespace ecs
