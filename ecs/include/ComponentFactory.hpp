/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#ifndef COMPONENTFACTORY_HPP_
#define COMPONENTFACTORY_HPP_

#include <functional>
#include <string>
#include "Entity.hpp"
#include "Registry.hpp"
#include <nlohmann/json_fwd.hpp>
#include <unordered_map>

namespace ecs {
    class ComponentFactory {
      public:
        enum class Mode { Server, Client };
        ComponentFactory(std::shared_ptr<Registry> &registry, Mode mode);
        ComponentFactory();
        ~ComponentFactory();

        Entity createEntity(const std::string &file);
        void createComponent(const Entity e, const std::string &component, const nlohmann::json &node);

      protected:
      private:
        std::shared_ptr<Registry> _r;

        void createPositionComponent(const Entity e, const nlohmann::json &node);
        void createDestroyableComponent(const Entity e, const nlohmann::json &node);
        void createSpriteComponent(const Entity e, const nlohmann::json &node);
        void createAnimationsComponent(const Entity e, const nlohmann::json &node);
        void createParallaxComponent(const Entity e, const nlohmann::json &node);
        void createTextComponent(const Entity e, const nlohmann::json &node);
        void createClickedComponent(const Entity e, const nlohmann::json &node);
        void createControllableComponent(const Entity e, const nlohmann::json &node);
        void createDrawableComponent(const Entity e, const nlohmann::json &node);
        void createFilledColorComponent(const Entity e, const nlohmann::json &node);
        void createHoverComponent(const Entity e, const nlohmann::json &node);
        void createMusicComponent(const Entity e, const nlohmann::json &node);
        void createOutlinedColorComponent(const Entity e, const nlohmann::json &node);
        void createScoreComponent(const Entity e, const nlohmann::json &node);
        void createShieldComponent(const Entity e, const nlohmann::json &node);
        void createSizeComponent(const Entity e, const nlohmann::json &node);
        void createSoundEffectComponent(const Entity e, const nlohmann::json &node);
        void createVelocityComponent(const Entity e, const nlohmann::json &node);
        void createLifeComponent(const Entity e, const nlohmann::json &node);
        std::unordered_map<std::string, std::function<void(const Entity, const nlohmann::json)>> functions;
    };

} // namespace ecs

#endif /* !COMPONENTFACTORY_HPP_ */
