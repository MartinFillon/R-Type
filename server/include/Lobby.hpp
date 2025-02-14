/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

#include <functional>
#include <map>
#include <vector>

#include "Server.hpp"
#include "TCPConnection.hpp"

#define LOBBY_SIZE_MAX 4

namespace rtype::server {

    class TCPConnection;

    class Lobby {

        using TCP = asio::ip::tcp;

      public:
        Lobby(const std::string &name, int port);

        bool start();
        bool assign(TCPConnection &client);
        bool unassign(TCPConnection &client);

        std::string getName() const
        {
            return _name;
        };

        size_t getNumberConnections() const
        {
            return _clients.size();
        };

        bool isRunning() const
        {
            return _running;
        };

        int getNumberReady();

      private:
        std::string _name;
        std::vector<std::reference_wrapper<TCPConnection>> _clients;

        std::shared_ptr<Server> _server;

        int _port;
        bool _running;
    };

}; // namespace rtype::server

#endif /* !LOBBY_HPP_ */
