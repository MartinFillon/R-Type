/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SystemsManager
*/

#pragma once

#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "IContext.hpp"
#include "Systems/ISystems.hpp"

namespace ecs {
    class Registry;
    class ComponentFactory;
} // namespace ecs

namespace ecs::systems {

    class SystemsManager {
      public:
        void runSystems(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> &ctx, ComponentFactory &f);

        template <typename T>
        void AddSystem(const std::string path)
        {
            std::ifstream file(path);
            const nlohmann::json j = nlohmann::json::parse(file);

            std::shared_ptr<ISystems> system = std::make_shared<T>(j);

            AddSystem(system);
        }

        template <typename T>
        void AddSystem()
        {
            std::shared_ptr<ISystems> system = std::make_shared<T>();

            AddSystem(system);
        }

        void AddSystem(std::shared_ptr<ISystems> &system);
        void AddSystem(ISystems *system);

      protected:
      private:
        std::vector<std::shared_ptr<ISystems>> __systems;
    };
}; // namespace ecs::systems
