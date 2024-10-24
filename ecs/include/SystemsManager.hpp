/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SystemsManager
*/

#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

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

            __systems.push_back(std::make_shared<T>(j));
        }

        void AddSystem(std::shared_ptr<ISystems> &system);
        void AddSystem(ISystems *system);

      protected:
      private:
        std::vector<std::shared_ptr<ISystems>> __systems;
    };
}; // namespace ecs::systems
