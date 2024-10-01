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

    switch (packet.getOpcode()) {
        case protocol::OBJECT_POSITION:
            std::cout << "OBJPOS\n";
            break;
        case protocol::NEW_OBJECT:
            std::cout << "NEWOBJ\n";
            break;
        case protocol::GAME_SPEED:
            std::cout << "GAMESP\n";
            break;
        case protocol::OBJECT_REMOVED:
            std::cout << "OBJREM\n";
            break;
        case protocol::NEW_PLAYER:
            std::cout << "NEWPL\n";
            break;
        case protocol::PLAYER_CRASHED:
            std::cout << "PLCRASH\n";
            break;
        case protocol::LEAVING:
            std::cout << "LEAV\n";
            break;
        case protocol::PLAYER_LEFT:
            std::cout << "PLLEFT\n";
            break;
        case protocol::WELCOME:
            std::cout << "HANDSH\n";
            break;
        case protocol::REFUSED:
            std::cout << "DENY\n";
            break;
        case protocol::READY:
            std::cout << "READ\n";
            break;
        case protocol::PING:
            std::cout << "PONG\n";
            break;
        case protocol::OBJECT_INFORMATIONS:
            std::cout << "OBJINFO\n";
            break;
        default:
            std::cout << INVALID_PACKET(id) << std::endl;
            return;
    }

    std::cout << packet.toMessage().data() << std::endl;

    std::cout << VALID_PACKET(id) << std::endl;
}

void Rtype::Game::update() {}
