/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SystemsManager
*/

#pragma once

#include <memory>
#include <vector>

#include "ComponentFactory.hpp"
#include "IContext.hpp"
#include "Registry.hpp"
#include "Systems/ISystems.hpp"

namespace ecs::systems {
    class SystemsManager {
      public:
        SystemsManager(const std::string config_file);
        ~SystemsManager();

        void runSystems(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> &ctx, ComponentFactory &f);

      protected:
      private:
        std::vector<std::shared_ptr<ISystems>> __systems;
    };
}; // namespace ecs::systems
