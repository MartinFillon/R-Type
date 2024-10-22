/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
    #define LOBBY_HPP_

    #include <vector>

    #include "Server.hpp"
    #include "IContext.hpp"
    #include "TCPConnection.hpp"

    #define LOBBY_SIZE_MAX 4

namespace rtype::server {

    class TCPConnection;

    class Lobby {

        public:

            Lobby(const std::string &name);

            void start();
            int assign(std::shared_ptr<TCPConnection> &client);
            int unassign(std::shared_ptr<TCPConnection> &client);

        private:

            std::string _name;
            std::vector<std::shared_ptr<TCPConnection>> _clients;

            std::shared_ptr<Server> _server;

            int _port;
            bool _running;

    };

};

#endif /* !LOBBY_HPP_ */