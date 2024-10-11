/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** RegistryWrapper
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Registry.hpp"
#include "TextureManager.hpp"

namespace rtype {

    class RegistryWrapper {
      public:
        RegistryWrapper();
        ~RegistryWrapper();

        void draw(sf::RenderWindow &, TextureManager &);

        std::shared_ptr<ecs::Registry> &getServerRegistry()
        {
            return _server;
        }

        std::shared_ptr<ecs::Registry> &getClientRegistry()
        {
            return _client;
        }

        void run_systems(std::shared_ptr<ecs::IContext> ctx);

      protected:
      private:
        std::shared_ptr<ecs::Registry> _client;
        std::shared_ptr<ecs::Registry> _server;
    };

} // namespace rtype
