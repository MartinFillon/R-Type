/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Lobby
*/

#include "Lobby.hpp"
#include <cstdlib>
#include <string>
#include "Context.hpp"
#include "IContext.hpp"
#include "Server.hpp"

rtype::server::Lobby::Lobby(const std::string &name, int port) : _name(name), _running(false), _port(port) {}

bool rtype::server::Lobby::start()
{
    for (auto &client : _clients) {
        if (!client.get().isReady()) {
            return false;
        }
    }

    _server = std::make_shared<Server>(_port);
    _running = true;

    std::shared_ptr<ecs::IContext> context = std::make_shared<rtype::server::Context>(_server);

    for (auto &client : _clients) {
        client.get().writeToClient("UDP:" + std::to_string(_port));
        client.get().setConnected(false);
    }

    return _server->run(context);
}

bool rtype::server::Lobby::assign(TCPConnection &client)
{
    if (_clients.size() == LOBBY_SIZE_MAX) {
        return false;
    }

    _clients.push_back(client);

    return true;
}

bool rtype::server::Lobby::unassign(TCPConnection &client)
{
    for (size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i].get().getId() == client.getId()) {
            _clients.erase(_clients.begin() + i);
            return true;
        }
    }

    return false;
};

int rtype::server::Lobby::getNumberReady()
{
    int count = 0;
    for (auto &client : _clients) {
        if (client.get().isReady() == true) {
            count += 1;
        }
    }
    return count;
}
