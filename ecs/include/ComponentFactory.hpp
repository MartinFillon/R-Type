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
    /// @brief ComponentFactory is a class that make component from a json configuration file
    class ComponentFactory {
      public:
        /// @brief Mode of the factory, they are different if we are server side or client side, client will load useful drawable component and server not
        enum class Mode { Server, Client };
        /// @brief Component Factory constructor, it will init an unorderd map of function and store it, string as a Key and function as a value
        /// @param registry is a shared pointer reference to the registry of the game
        /// @param mode is to set the mode, actions will be different if we are a server or a Client
        ComponentFactory(std::shared_ptr<Registry> &registry, Mode mode);
        ComponentFactory();
        ~ComponentFactory();

        /// @brief createEntity method will create an entity and will entirely set in the registry, in the SparseArray.
        /// @param file is the path to the config json file
        /// @return an new Entity
        Entity createEntity(const std::string &file);
        /// @brief createComponent a component by the string, entity and the node in the json config file
        /// @param e is the entity we want to set the compnent
        /// @param component is the component we want
        /// @param node is the node in the json config file
        void createComponent(const Entity e, const std::string &component, const nlohmann::json &node);

      protected:
      private:
        /// @brief shared pointer of the Registry shared with the game client
        std::shared_ptr<Registry> _r;

        /// @brief Create Position component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createPositionComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Destroy component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createDestroyableComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Sprite component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createSpriteComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Animations component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createAnimationsComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Parallax component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createParallaxComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Text component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createTextComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Clicked component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createClickedComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Controllable component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createControllableComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Drawable component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createDrawableComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Filled color component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createFilledColorComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Hover component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createHoverComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Music component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createMusicComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Outlined Color component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createOutlinedColorComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Score component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createScoreComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Shield component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createShieldComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Size component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createSizeComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Sound Effect component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createSoundEffectComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Velocity component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createVelocityComponent(const Entity e, const nlohmann::json &node);
        /// @brief Create Life component to set it to the entity we want to create
        /// @param e is the entity
        /// @param node is the node in the json config file
        void createLifeComponent(const Entity e, const nlohmann::json &node);
        /// @brief functions is the map of name component (string) as key and function (create[name]Component) as value to create the component
        std::unordered_map<std::string, std::function<void(const Entity, const nlohmann::json)>> functions;
    };

} // namespace ecs

#endif /* !COMPONENTFACTORY_HPP_ */
