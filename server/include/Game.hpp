/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <queue>
#include "ComponentFactory.hpp"
#define UNUSED __attribute__((unused))

#define INVALID_PACKET(x) "Invalid packet from client [" << x << "]"
#define VALID_PACKET(x) "Valid packet from client [" << x << "]"

#include <iostream>

#include "Packet.hpp"
#include "Registry.hpp"

namespace Rtype {

    /// @brief Class to wrap all the utilities of the game loop and logic with the ECS.
    class Game {

      public:
        /// @brief Generate a `Game` creating in the process the ECS's registry `_r` and initializing all the game.
        Game();

        /// @brief Runs the updating loop of the game and add all the updated informations to the packet queue.
        void update();
        /// @brief Handles the case when a player leaves the game and disconnects from the server by removing its entity
        /// and opening its occupied place for new players to join.
        /// @param player_place a `const unsigned int` representing the player's place between `FIRST_PLAYER_PLACE` and
        /// the `MAX_PLAYER_PLACES`.
        void handleLeaving(const unsigned int player_place);

        /// @brief Get the packet queue of all the packets needed to be sent to the clients for update.
        /// @return `std::queue<Packet> &` of the packets containing all the updated informations since the last tick.
        /// The returned value is always at least an empty queue.
        std::queue<Packet> &getPacketsToSend()
        {
            return _packetsToSend;
        }

        /// @brief Creates a player entity in the ECS's registry `_r` and replaces the previous stored player entity at
        /// the `player_place` position by the newly created entity.
        /// @param player_place a `const unsigned int` representing the player's place between `FIRST_PLAYER_PLACE` and
        /// the `MAX_PLAYER_PLACES`.
        void createPlayer(const unsigned int player_place);
        /// @brief Moves the player at the `player_place` in the direction `dir` in the ECS's registry `_r`.
        /// @param player_place a `const unsigned int` representing the player's place between `FIRST_PLAYER_PLACE` and
        /// the `MAX_PLAYER_PLACES`.
        /// @param dir a `const int` representing the player's direction in the `protocol::Direction` enum.
        void movePlayer(const int player_place, const int dir);
        /// @brief Makes the player at the `player_place` shoot a projectile in the ECS's registry `_r`.
        /// @param player_place a `const unsigned int` representing the player's place between `FIRST_PLAYER_PLACE` and
        /// the `MAX_PLAYER_PLACES`.
        void makePlayerShoot(const int player_place);

      private:
        /// @brief The ECS's registry which stores and interacts with all entities and components.
        std::shared_ptr<ecs::Registry> _r;
        /// @brief The ECS's component factory which creates the entities and the components from .json configs files.
        ecs::ComponentFactory _cf;
        /// @brief The list of the players entities ids indexed by the player's place.
        std::unordered_map<int, int> _players_entities_ids;
        /// @brief The queue of the packets containing the updated data since the last tick to be sent to the clients.
        std::queue<Packet> _packetsToSend;

        /// @brief Creates a `Packet` of the player movement to be queued in the `_packetsToSend` queue.
        /// @param p a `const std::optional<ecs::component::Position> &` representing the player's entity position
        /// component.
        /// @param entity_id an `int` representing the player's entity id.
        void preparePosition(const std::optional<ecs::component::Position> &p, int entity_id);
    };

}; // namespace Rtype

#endif /* !GAME_HPP_ */
