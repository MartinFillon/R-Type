/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SystemsManager
*/

#pragma once

#include <memory>
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
        SystemsManager(const std::string config_file);
        ~SystemsManager();

        void runSystems(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> &ctx, ComponentFactory &f);

      protected:
      private:
        void add_system(const std::string name);

        std::vector<std::shared_ptr<ISystems>> __systems;
    };
}; // namespace ecs::systems
