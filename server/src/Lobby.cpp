/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Lobby
*/

#include "Lobby.hpp"
#include "IContext.hpp"
#include "Context.hpp"
#include "Server.hpp"
#include <cstdlib>

rtype::server::Lobby::Lobby(const std::string &name): _name(name), _running(false)
{
}

bool rtype::server::Lobby::start(std::shared_ptr<ecs::IContext> &context)
{
    for (auto &client: _clients) {
        if (!client.get().isReady()) {
            return false;
        }
    }

    (void)context;

    static int portUdp = 1234;

    _server = std::make_shared<Server>(portUdp);
    portUdp++;
    std::shared_ptr<ecs::IContext> vraiContext = std::make_shared<rtype::server::Context>(_server);
    _running = true;
    return _server->run(vraiContext);
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