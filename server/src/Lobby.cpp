/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Lobby
*/

#include "Lobby.hpp"
#include <cstdlib>

rtype::server::Lobby::Lobby(const std::string &name): _name(name), _clients({}), _running(false)
{
}

void rtype::server::Lobby::start()
{
}

bool rtype::server::Lobby::assign(TCPConnection &client)
{
    if (_clients.size() == LOBBY_SIZE_MAX) {
        return false;
    }

    _clients.push_back(client);
    client.setLobby(_name);
    return true;
}

bool rtype::server::Lobby::unassign(TCPConnection &client)
{
    for (int i = 0; i < _clients.size(); i++) {
        if (_clients[i].get().getId() == client.getId()) {
            _clients.erase(_clients.begin() + i);
            client.setLobby("");
            return true;
        }
    }

    return false;
};