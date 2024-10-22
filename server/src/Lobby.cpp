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

int rtype::server::Lobby::assign(std::shared_ptr<TCPConnection> &client)
{
    if (_clients.size() == LOBBY_SIZE_MAX) {
        return EXIT_FAILURE;
    }

    _clients.push_back(std::move(client));
    client->setLobby(_name);
    return EXIT_SUCCESS;
}

int rtype::server::Lobby::unassign(std::shared_ptr<TCPConnection> &client)
{
    for (size_t i = 0; _clients[i]; i++) {
        if (client == _clients[i]) {
            _clients.erase(_clients.begin() + 1);
        }
    }
    client->setLobby("");
    return EXIT_SUCCESS;
}