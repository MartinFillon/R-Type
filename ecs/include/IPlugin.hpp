/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** IPlugin
*/

#pragma once

#include <memory>

namespace ecs {
    class Registry;
    class ComponentFactory;

    class IPlugin {
      public:
        virtual ~IPlugin() = default;

        virtual void run(std::shared_ptr<Registry> &r, std::shared_ptr<ComponentFactory>) = 0;

      protected:
      private:
    };
}; // namespace ecs
