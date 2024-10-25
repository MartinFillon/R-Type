/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#ifndef COMPONENTFACTORY_HPP_
#define COMPONENTFACTORY_HPP_

#include <exception>
#define CONFIG_BACKGROUND_0 "./config/background/background.json"
#define CONFIG_BACKGROUND_2 "./config/background/background_2.json"
#define CONFIG_BACKGROUND_3 "./config/background/background_3.json"
#define CONFIG_BACKGROUND_4 "./config/background/background_4.json"

#define CONFIG_PLAYER_0 "./config/player0.json"
#define CONFIG_PLAYER_1 "./config/player1.json"
#define CONFIG_PLAYER_2 "./config/player2.json"
#define CONFIG_PLAYER_3 "./config/player3.json"

#define CONFIG_ENNEMIES "./config/ennemies.json"
#define CONFIG_MILEPATES "./config/milepates.json"
#define CONFIG_BOSS "./config/boss.json"
#define CONFIG_PROJECTILE "./config/projectile.json"
#define CONFIG_PLAYER_PROJECTILE "./config/playerProjectile.json"

#define ERROR_FILE_NOT_FOUND(file) "File not found on: [" + file + "]"
#define ERROR_PARSING_ERROR(file) "Parsing Error on : [" + file + "]"

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <nlohmann/json-schema.hpp>
#include <unordered_map>

#include "DlLoader.hpp"
#include "Entity.hpp"
#include "SystemsManager.hpp"

std::string getEnvOrDefault(const std::string &env, const std::string &def);

namespace ecs {
    class Registry;

    class ComponentFactory {
      public:
        class Error : public std::exception {
          public:
            virtual ~Error() = default;

            virtual const char *what() const noexcept = 0;
        };

        class ComponentNotCreated : public Error {
          public:
            ComponentNotCreated(const std::string &file)
            {
                _error = "Component for " + file + " not created";
            };

            const char *what() const noexcept override
            {
                return _error.c_str();
            }

          private:
            std::string _error;
        };

        using ComponentLoader = DlLoader<void, std::shared_ptr<Registry> &, Entity &, const nlohmann::json &>;

        ComponentFactory();
        ~ComponentFactory();

        class ComponentFactoryException {
            public:
              ComponentFactoryException(const std::string &error): _what(error) {}
              ~ComponentFactoryException() = default;

              const char *what() const noexcept {
                return _what.c_str();
              }
            private:
              std::string _what;
        };

        void registerComponent(std::string &name, std::string &path);
        Entity createEntity(std::shared_ptr<Registry> r, const std::string &file);
        Entity createEntity(std::shared_ptr<Registry> r, int id, const std::string &file);
        void createComponent(
            std::shared_ptr<Registry> r,
            const Entity e,
            const std::string &component,
            const nlohmann::json &node
        );

      protected:
      private:
        std::unordered_map<std::string, std::shared_ptr<ComponentLoader>> components;
        nlohmann::json _schema;
        nlohmann::json_schema::json_validator _validator;
    };

} // namespace ecs

#endif /* !COMPONENTFACTORY_HPP_ */
