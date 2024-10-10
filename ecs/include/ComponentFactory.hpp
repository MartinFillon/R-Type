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
    /// @brief Class to wrap all the necessary functions to build components from json configs.
    class ComponentFactory {
      public:
        /// @brief `enum` representing the mode of the component factory, server's one is much more complete than client's one.
        enum class Mode { Server, Client };

        /// @brief Generates a `ComponentFactory` creating in the process an unorderd map of function and store it, string as a Key and function as a value.
        /// @param registry a `std::shared_ptr<Registry> &` representing the reference of the registry of the game.
        /// @param mode `Mode::*` representing the mode of the component factory, actions will be different server and client versions.
        ComponentFactory(std::shared_ptr<Registry> &registry, Mode mode);

        /// @brief Generates an empty `ComponentFactory`
        /// @deprecated use `ComponentFactory(std::shared_ptr<Registry> &registry, Mode mode)` instead.
        ComponentFactory();

        ~ComponentFactory();

        /// @brief Creates an `Entity` and will entirely set it up in the registry `_r`.
        /// @param file a `const std::string&` representing the reference to the json config file of the newly created entity.
        /// @return `Entity` representing the newly created entity.
        Entity createEntity(const std::string &file);

        /// @brief Creates a component by linking the factory's functions map and the given `component` string into the given entity `e` from the given json node reference `node`.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param component a `const std::string &` representing the reference of the name of the component to add to the entity.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createComponent(const Entity e, const std::string &component, const nlohmann::json &node);

      protected:
      private:
        /// @brief The client's registry which stores and interacts with all entities and components.
        std::shared_ptr<Registry> _r;

        /// @brief Creates a `ecs::component::Position` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createPositionComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Destroyable` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createDestroyableComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Sprite` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createSpriteComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Animation` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createAnimationsComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Parallax` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createParallaxComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Text` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createTextComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Clicked` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createClickedComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Controllable` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createControllableComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Drawable` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createDrawableComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::FilledColor` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createFilledColorComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Hover` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createHoverComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Music` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createMusicComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::OutlinedColor` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createOutlinedColorComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Score` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createScoreComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Shield` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createShieldComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Size` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createSizeComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::SoundEffect` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createSoundEffectComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Velocity` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createVelocityComponent(const Entity e, const nlohmann::json &node);

        /// @brief Creates a `ecs::component::Life` component to link it to the entity in the creation process.
        /// @param e a `const Entity` representing the entity to which to add the new component.
        /// @param node a `const nlohmann:json &` representing the reference of the json node from which the new component will be created.
        void createLifeComponent(const Entity e, const nlohmann::json &node);

        /// @brief The map of the factory's functions indexed by an `std::string` key is the map of name component (string) as key and function (create[name]Component) as value to create the component
        std::unordered_map<std::string, std::function<void(const Entity, const nlohmann::json)>> functions;
    };

} // namespace ecs

#endif /* !COMPONENTFACTORY_HPP_ */
