/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** PluginManager
*/

#pragma once

#include <memory>
#include <vector>
#include "IPlugin.hpp"

namespace ecs {
    class PluginManager {
      public:
        PluginManager() = default;
        ~PluginManager() = default;

      protected:
      private:
        std::vector<std::shared_ptr<IPlugin>> _plugins;
    };
} // namespace ecs
