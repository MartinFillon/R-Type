/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Lobby
*/

#include "Lobby.hpp"
#include <cstdlib>

rtype::server::Lobby::Lobby(const std::string &name): _name(name), _running(false)
{
}

void rtype::server::Lobby::start()
{
}

bool rtype::server::Lobby::assign(unsigned int id)
{
    if (_clients.size() == LOBBY_SIZE_MAX) {
        return false;
    }

    _clients.push_back(id);

    return true;
}

bool rtype::server::Lobby::unassign(unsigned int id)
{
    for (size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i] == id) {
            _clients.erase(_clients.begin() + i);
            return true;
        }
    }

    return false;
};