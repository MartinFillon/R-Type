/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #define UNUSED __attribute__((unused))

    #include "Packet.hpp"

namespace Rtype {

    class Game {

        public:

            Game() = default;

            void update() {};
            void processAction(UNUSED const int id, UNUSED const Packet &packet) {};

    };

};

#endif /* !GAME_HPP_ */
