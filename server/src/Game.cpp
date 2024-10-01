/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include "Game.hpp"

#include "protocol.hpp"

void Rtype::Game::processAction(const unsigned int id, const Packet &packet)
{
    if (!packet.isValid()) {
        std::cout << INVALID_PACKET(id) << std::endl;
        return;
    }

    std::cout << VALID_PACKET(id) << std::endl;
}

void Rtype::Game::update()
{}
