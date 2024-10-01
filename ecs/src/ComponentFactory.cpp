/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#include <SFML/System/Clock.hpp>
#include <fstream>
#include <functional>
#include <memory>

#include <nlohmann/json.hpp>

#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Parallax.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Registry.hpp"

namespace ecs {
    ComponentFactory::ComponentFactory() {}

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

        functions["text"] = [this](const Entity e, const nlohmann::json &node) { createTextComponent(e, node); };
        functions["clicked"] = [this](const Entity e, const nlohmann::json &node) { createClickedComponent(e, node); };
        functions["controllable"] = [this](const Entity e, const nlohmann::json &node) {
            createControllableComponent(e, node);
        };
        functions["filledColor"] = [this](const Entity e, const nlohmann::json &node) {
            createFilledColorComponent(e, node);
        };
        functions["hover"] = [this](const Entity e, const nlohmann::json &node) { createHoverComponent(e, node); };
        functions["music"] = [this](const Entity e, const nlohmann::json &node) { createMusicComponent(e, node); };
        functions["outlinedColor"] = [this](const Entity e, const nlohmann::json &node) {
            createOutlinedColorComponent(e, node);
        };
        functions["score"] = [this](const Entity e, const nlohmann::json &node) { createScoreComponent(e, node); };
        functions["shield"] = [this](const Entity e, const nlohmann::json &node) { createShieldComponent(e, node); };
        functions["soundEffect"] = [this](const Entity e, const nlohmann::json &node) {
            createSoundEffectComponent(e, node);
        };
        functions["velocity"] = [this](const Entity e, const nlohmann::json &node) {
            createVelocityComponent(e, node);
        };
    }

    ComponentFactory::~ComponentFactory() {}

    void ComponentFactory::createEntity(const std::string &file)
    {
        std::ifstream f(file);
        nlohmann::json config = nlohmann::json::parse(f);

        Entity e = _r->spawn_entity();
        _r->_entities.addEntity(e);

        for (auto &c : config["active"]) {
            createComponent(e, c, config["components"][c]);
        }
    }

    void ComponentFactory::createComponent(const Entity e, const std::string &name, const nlohmann::json &node)
    {
        functions[name](e, node);
    }

    void ComponentFactory::createPositionComponent(const Entity e, const nlohmann::json &node)
    {
        auto &pos_array = _r->register_if_not_exist<component::Position>();

        pos_array[e.getId()] = component::Position{node["x"], node["y"]};
    }

    void ComponentFactory::createDrawableComponent(const Entity e, const nlohmann::json &node)
    {
        auto &drawable_array = _r->register_if_not_exist<component::Drawable>();

        drawable_array[e.getId()] = component::Drawable{node};
    }

    void ComponentFactory::createSpriteComponent(const Entity e, const nlohmann::json &node)
    {
        auto &sprite_array = _r->register_if_not_exist<component::Sprite>();

        sprite_array[e.getId()] = component::Sprite{node};
    }

    void ComponentFactory::createAnimationsComponent(const Entity e, const nlohmann::json &node)
    {
        auto &animations_array = _r->register_if_not_exist<component::Animations>();

        component::Object type = component::Background;
        if (node["type"] == "player")
            type = component::Player;
        else if (node["type"] == "weapon")
            type = component::Weapon;
        else if (node["type"] == "ennemies")
            type = component::Ennemies;
        else if (node["type"] == "background")
            type = component::Background;

        animations_array[e.getId()] = component::Animations{
            sf::Clock(), node["width"], node["height"], node["x"], node["y"], node["rotation"], type
        };
    }

    void ComponentFactory::createParallaxComponent(const Entity e, const nlohmann::json &node)
    {
        auto &parallax_array = _r->register_if_not_exist<component::Parallax>();

        parallax_array[e.getId()] = component::Parallax{node["active"], node["speed"], node["multiplier"]};
    }

    void ComponentFactory::createSizeComponent(const Entity e, const nlohmann::json &node)
    {
        auto &size_array = _r->register_if_not_exist<component::Size>();

        size_array[e.getId()] = component::Size{node["width"], node["height"]};
    }

    void ComponentFactory::createTextComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createClickedComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createControllableComponent(const Entity e, const nlohmann::json &node)
    {
        auto &controllable_array = _r->register_if_not_exist<component::Controllable>();

        controllable_array[e.getId()] = component::Controllable{node["controllable"], node["speed"]};
    }

    void ComponentFactory::createFilledColorComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createHoverComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createMusicComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createOutlinedColorComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createScoreComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createShieldComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createSoundEffectComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createVelocityComponent(const Entity e, const nlohmann::json &node) {}
} // namespace ecs
