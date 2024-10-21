/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ComponentFactory
*/

#ifndef COMPONENTFACTORY_HPP_
#define COMPONENTFACTORY_HPP_

#include <memory>
#define CONFIG_BACKGROUND_0 "config/background/background.json"
#define CONFIG_BACKGROUND_2 "config/background/background_2.json"
#define CONFIG_BACKGROUND_3 "config/background/background_3.json"
#define CONFIG_BACKGROUND_4 "config/background/background_4.json"

#define CONFIG_PLAYER_0 "config/player0.json"
#define CONFIG_PLAYER_1 "config/player1.json"
#define CONFIG_PLAYER_2 "config/player2.json"
#define CONFIG_PLAYER_3 "config/player3.json"

#define CONFIG_ENNEMIES "config/ennemies.json"
#define CONFIG_MILEPATES "config/milepates.json"
#define CONFIG_BOSS "config/boss.json"
#define CONFIG_PROJECTILE "config/projectile.json"
#define CONFIG_PLAYER_PROJECTILE "config/playerProjectile.json"

#include <string>
#include "ComponentLoader.hpp"
#include "Entity.hpp"
#include <nlohmann/json_fwd.hpp>
#include <unordered_map>

std::string getEnvOrDefault(const std::string &env, const std::string &def);

namespace ecs {
    class Registry;

    class ComponentFactory {
      public:
        ComponentFactory();
        ~ComponentFactory();

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
    };

} // namespace ecs

#endif /* !COMPONENTFACTORY_HPP_ */
