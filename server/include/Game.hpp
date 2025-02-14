/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include "Components/Position.hpp"
#include "Entity.hpp"
#include "IContext.hpp"
#define UNUSED __attribute__((unused))

#define INVALID_PACKET(x) "Invalid packet from client [" << x << "]"
#define VALID_PACKET(x) "Valid packet from client [" << x << "]"

#define FRAME_PER_SECONDS(x) (int)(1 / x)

#define SERVER_TPS 20

#include "ComponentFactory.hpp"
#include "Registry.hpp"

namespace rtype::server {

    /// @brief Class to wrap all the utilities of the game loop and logic with the ECS.
    class Game {

      public:
        /// @brief Generate a `Game` creating in the process the ECS's registry `_r` and initializing all the game.
        Game();

        /// @brief Runs the updating loop of the game and add all the updated informations to the packet queue.
        /// @param are_any_clients_connected `true` if any number of clients are connected and packets need to be
        /// created, `false` otherwise.
        /// @param ctx a `std::shared_ptr<ecs::IContext>` representing the reference to the global context of the game.
        void update(bool are_any_clients_connected, std::shared_ptr<ecs::IContext> &ctx);

        /// @brief Handles the case when a player leaves the game and disconnects from the server by removing its entity
        /// and opening its occupied place for new players to join.
        /// @param player_place a `const unsigned int` representing the player's place between `FIRST_PLAYER_PLACE` and
        /// the `MAX_PLAYER_PLACES`.
        void handleLeaving(const unsigned int player_place);

        /// @brief Creates a player entity in the ECS's registry `_r` and replaces the previous stored player entity at
        /// the `player_place` position by the newly created entity.
        /// @param player_place a `const unsigned int` representing the player's place between `FIRST_PLAYER_PLACE` and
        /// the `MAX_PLAYER_PLACES`.
        /// @return an `ecs::Entity` representing the newly created player entity.
        ecs::Entity createPlayer(const unsigned int player_place);

        /// @brief Moves the player at the `player_place` in the direction `dir` in the ECS's registry `_r`.
        /// @param player_place a `const int` representing the player's place between `FIRST_PLAYER_PLACE` and
        /// the `MAX_PLAYER_PLACES`.
        /// @param dir a `const int` representing the player's direction in the `protocol::Direction` enum.
        void movePlayer(const int player_place, const int dir);

        /// @brief Makes the player at the `player_place` shoot a projectile in the ECS's registry `_r`.
        /// @param player_place a `const int` representing the player's place between `FIRST_PLAYER_PLACE` and
        /// the `MAX_PLAYER_PLACES`.
        void makePlayerShoot(const int player_place);

        /// @brief Get the ECS registry of the server managing the game.
        /// @return a `std::shared_ptr<ecs::Registry>` representing the registry of the server managing the game.
        std::shared_ptr<ecs::Registry> getRegistry();

        /// @brief Get the player's entity id by the given `player_place`.
        /// @param player_place a `const int` representing the player's place between `FIRST_PLAYER_PLACE` and
        /// the `MAX_PLAYER_PLACES`.
        /// @return `const int` representing the player's entity id.
        const int getPlayerEntityIdByPlace(const int player_place);

        /// @brief Get the player's place by the given `player_entity_id`.
        /// @param player_entity_id a `const int` representing the player's entity id.
        /// @return `const int` representing the player's place between `FIRST_PLAYER_PLACE` and
        /// the `MAX_PLAYER_PLACES`.
        const int getPlaceByPlayerEntityId(const int player_entity_id);

        /// @brief Creates a `Packet` of the player movement to be queued in the `_packetsToSend` queue.
        /// @param p a `const std::optional<ecs::component::Position> &` representing the reference to the player's
        /// entity position component.
        /// @param entity_id an `int` representing the player's entity id.
        void preparePosition(const std::optional<ecs::component::Position> &p, int entity_id);

        /// @brief Setups the destroy logic
        void setupDestroy();
        /// @brief Setups the collisions logic
        void setupCollisons();
        /// @brief Setups the bosses logic
        void setupBosses();
        /// @brief Setups the base ennemies logic
        void setupBasicEnnemies();
        /// @brief Setups the background logic
        void setupBackground();

      private:
        /// @brief The ECS's registry which stores and interacts with all entities and components.
        std::shared_ptr<ecs::Registry> _r;
        /// @brief The ECS's component factory which creates the entities and the components from .json configs files.
        ecs::ComponentFactory _cf;
        /// @brief The map of the players entities ids indexed by the players places.
        std::unordered_map<int, int> _players_entities_ids;

        /// @brief The ECS's context managing all the said ECS.
        std::shared_ptr<ecs::IContext> _ctx;

        /// @brief The game's clock which counts ticks.
        ecs::Clock _systemClock;
    };

}; // namespace rtype::server

#endif /* !GAME_HPP_ */
