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

    class Game {

      public:
        Game();

        void update();
        void handleLeaving(const unsigned int id);

        std::queue<Packet> &getPacketsToSend()
        {
            return _packetsToSend;
        }

        void createPlayer(const unsigned int id);

      private:
        std::shared_ptr<ecs::Registry> _r;
        ecs::ComponentFactory _cf;
        std::unordered_map<unsigned int, ecs::Entity> _players;
        std::queue<Packet> _packetsToSend;

        void preparePosition(const std::optional<ecs::component::Position> &p, int i);
    };

}; // namespace Rtype

#endif /* !GAME_HPP_ */
