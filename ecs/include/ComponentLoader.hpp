/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentLoader
*/

#pragma once

#include "DlLoader.hpp"
#include "Entity.hpp"
#include <nlohmann/json_fwd.hpp>

namespace ecs {
    class Registry;

    class ComponentLoader {
      public:
        ComponentLoader(std::string path) : loader(path, "register_component") {}

        ComponentLoader() {}

        void call(std::shared_ptr<Registry> &r, Entity &e, const nlohmann::json &node)
        {
            loader.call(r, e, node);
        }

        ~ComponentLoader() {};

      protected:
      private:
        DlLoader<void, std::shared_ptr<Registry> &, Entity &, const nlohmann::json &> loader;
    };

} // namespace ecs
