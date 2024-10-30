/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#ifndef COMPONENTFACTORY_HPP_
#define COMPONENTFACTORY_HPP_

#include <dylib.hpp>
#include <exception>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <nlohmann/json-schema.hpp>
#include <unordered_map>

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

        using ComponentLoader = dylib;

        ComponentFactory();
        ~ComponentFactory();

        class ComponentFactoryException {
          public:
            ComponentFactoryException(const std::string &error) : _what(error) {}

            ~ComponentFactoryException() = default;

            const char *what() const noexcept
            {
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
