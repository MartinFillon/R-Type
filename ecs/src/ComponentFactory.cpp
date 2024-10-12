/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#include <fstream>
#include <functional>
#include <memory>

#include <nlohmann/json.hpp>

#include "Clock.hpp"
#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Clicked.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/FilledColor.hpp"
#include "Components/Hover.hpp"
#include "Components/Life.hpp"
#include "Components/OutlinedColor.hpp"
#include "Components/Parallax.hpp"
#include "Components/Position.hpp"
#include "Components/Score.hpp"
#include "Components/Shield.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Components/Text.hpp"
#include "Components/Velocity.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

namespace ecs {
    ComponentFactory::ComponentFactory() {}

    ComponentFactory::ComponentFactory(std::shared_ptr<Registry> &r, Mode mode) : _r(r)
    {
        functions["position"] = [this](const Entity e, const nlohmann::json &node) {
            createPositionComponent(e, node);
        };

        if (mode == Mode::Client) {
            functions["destroyable"] = [this](const Entity e, const nlohmann::json &node) {
                createDestroyableComponent(e, node);
            };
            functions["drawable"] = [this](const Entity e, const nlohmann::json &node) {
                createDrawableComponent(e, node);
            };
            functions["sprite"] = [this](const Entity e, const nlohmann::json &node) {
                createSpriteComponent(e, node);
            };
            functions["animations"] = [this](const Entity e, const nlohmann::json &node) {
                createAnimationsComponent(e, node);
            };

            functions["parallax"] = [this](const Entity e, const nlohmann::json &node) {
                createParallaxComponent(e, node);
            };
            functions["text"] = [this](const Entity e, const nlohmann::json &node) { createTextComponent(e, node); };
            functions["clicked"] = [this](const Entity e, const nlohmann::json &node) {
                createClickedComponent(e, node);
            };
            functions["music"] = [this](const Entity e, const nlohmann::json &node) { createMusicComponent(e, node); };
            functions["soundEffect"] = [this](const Entity e, const nlohmann::json &node) {
                createSoundEffectComponent(e, node);
            };
            functions["filledColor"] = [this](const Entity e, const nlohmann::json &node) {
                createFilledColorComponent(e, node);
            };
            functions["hover"] = [this](const Entity e, const nlohmann::json &node) { createHoverComponent(e, node); };
            functions["outlinedColor"] = [this](const Entity e, const nlohmann::json &node) {
                createOutlinedColorComponent(e, node);
            };
            functions["life"] = [this](const Entity e, const nlohmann::json &node) { createLifeComponent(e, node); };
        }

        functions["life"] = [this](const Entity e, const nlohmann::json &node) { createLifeComponent(e, node); };

        functions["size"] = [this](const Entity e, const nlohmann::json &node) { createSizeComponent(e, node); };
        functions["controllable"] = [this](const Entity e, const nlohmann::json &node) {
            createControllableComponent(e, node);
        };
        functions["score"] = [this](const Entity e, const nlohmann::json &node) { createScoreComponent(e, node); };
        functions["shield"] = [this](const Entity e, const nlohmann::json &node) { createShieldComponent(e, node); };
        functions["velocity"] = [this](const Entity e, const nlohmann::json &node) {
            createVelocityComponent(e, node);
        };
    }

    ComponentFactory::~ComponentFactory() {}

    Entity ComponentFactory::createEntity(const std::string &file)
    {
        // std::cerr << "Creating entity from file: " << file << std::endl;
        std::ifstream f(file);
        nlohmann::json config = nlohmann::json::parse(f);

        Entity e = _r->spawn_entity();
        _r->_entities.addEntity(e.getId());

        for (auto &c : config["active"]) {
            createComponent(e, c, config["components"][c]);
        }
        return e;
    }

    Entity ComponentFactory::createEntity(int id, const std::string &file)
    {
        // std::cerr << "Creating entity from file: " << file << " with id " << id << std::endl;
        std::ifstream f(file);
        nlohmann::json config = nlohmann::json::parse(f);

        Entity e = Entity(id);
        _r->_entities.addEntity(e.getId());

        for (auto &c : config["active"]) {
            createComponent(e, c, config["components"][c]);
        }
        return e;
    }

    void ComponentFactory::createComponent(const Entity e, const std::string &name, const nlohmann::json &node)
    {
        if (functions.find(name) != functions.end())
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

    void ComponentFactory::createDestroyableComponent(const Entity e, const nlohmann::json &node)
    {
        auto &destroyable_array = _r->register_if_not_exist<component::Destroyable>();

        destroyable_array[e.getId()] = component::Destroyable{node};
    }

    void ComponentFactory::createAnimationsComponent(const Entity e, const nlohmann::json &node)
    {
        auto &animations_array = _r->register_if_not_exist<component::Animations>();

        component::Object type = component::Background;
        component::Type ennemiesType = component::Type::None;

        if (node["objectType"] == "boss")
            ennemiesType = component::Type::Boss;
        else if (node["objectType"] == "basic")
            ennemiesType = component::Type::Basic;
        else if (node["objectType"] == "milepates")
            ennemiesType = component::Type::Milespates;

        if (node["type"] == "player")
            type = component::Player;
        else if (node["type"] == "weapon")
            type = component::Weapon;
        else if (node["type"] == "ennemies")
            type = component::Ennemies;
        else if (node["type"] == "background")
            type = component::Background;

        animations_array[e.getId()] = component::Animations{
            ecs::Clock(), node["width"], node["height"], node["x"], node["y"], node["rotation"], type, ennemiesType
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

    void ComponentFactory::createTextComponent(const Entity e, const nlohmann::json &node)
    {
        auto &text_array = _r->register_if_not_exist<component::Text>();

        text_array[e.getId()] = component::Text{node["string"]};
    }

    void ComponentFactory::createClickedComponent(const Entity e, const nlohmann::json &node)
    {
        auto &clicked_array = _r->register_if_not_exist<component::Clicked>();

        clicked_array[e.getId()] = component::Clicked{node["value"]};
    }

    void ComponentFactory::createControllableComponent(const Entity e, const nlohmann::json &node)
    {
        auto &controllable_array = _r->register_if_not_exist<component::Controllable>();

        controllable_array[e.getId()] = component::Controllable{node["controllable"], node["speed"]};
    }

    void ComponentFactory::createFilledColorComponent(const Entity e, const nlohmann::json &node)
    {
        auto &filled_color_array = _r->register_if_not_exist<component::FilledColor>();

        filled_color_array[e.getId()] = component::FilledColor{node["r"], node["g"], node["b"], node["a"]};
    }

    void ComponentFactory::createHoverComponent(const Entity e, const nlohmann::json &node)
    {
        auto &hover_array = _r->register_if_not_exist<component::Hover>();

        hover_array[e.getId()] = component::Hover{node["value"]};
    }

    void ComponentFactory::createMusicComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createOutlinedColorComponent(const Entity e, const nlohmann::json &node)
    {
        auto &outlined_color_array = _r->register_if_not_exist<component::OutlinedColor>();

        outlined_color_array[e.getId()] = component::OutlinedColor{node["r"], node["g"], node["b"], node["a"]};
    }

    void ComponentFactory::createScoreComponent(const Entity e, const nlohmann::json &node)
    {
        auto &score_array = _r->register_if_not_exist<component::Score>();

        score_array[e.getId()] = component::Score{node["value"]};
    }

    void ComponentFactory::createShieldComponent(const Entity e, const nlohmann::json &node)
    {
        auto &shield_array = _r->register_if_not_exist<component::Shield>();

        shield_array[e.getId()] = component::Shield{node["value"]};
    }

    void ComponentFactory::createSoundEffectComponent(const Entity e, const nlohmann::json &node) {}

    void ComponentFactory::createVelocityComponent(const Entity e, const nlohmann::json &node)
    {
        auto &velocity_array = _r->register_if_not_exist<component::Velocity>();

        velocity_array[e.getId()] = component::Velocity{node["x"], node["y"]};
    }

    void ComponentFactory::createLifeComponent(const Entity e, const nlohmann::json &node)
    {
        auto &life_array = _r->register_if_not_exist<component::Life>();

        life_array[e.getId()] = component::Life{node};
    }
} // namespace ecs
