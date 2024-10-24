/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
    #define LOBBY_HPP_

    #include <functional>
    #include <vector>
    #include <map>

    #include "Server.hpp"
    #include "TCPConnection.hpp"

    #define LOBBY_SIZE_MAX 4

namespace rtype::server {

    class TCPConnection;

    class Lobby {

        using TCP = asio::ip::tcp;

        public:

            Lobby(const std::string &name);

            bool start(std::shared_ptr<ecs::IContext> &context);
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

        private:

            std::string _name;
            std::vector<std::reference_wrapper<TCPConnection>> _clients;

            std::shared_ptr<Server> _server;

            int _port;
            bool _running;

    };

};

#endif /* !LOBBY_HPP_ */