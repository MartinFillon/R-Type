/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** TCPconnection
*/

#ifndef TCPCONNECTION_HPP_
    #define TCPCONNECTION_HPP_

    #include <asio.hpp>

    #include "Lobby.hpp"

    #define MAX_LOBBIES 4

namespace rtype::server {

    class Lobby;

    using TCP = asio::ip::tcp;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection> {

        public:

            TCPConnection(TCP::socket socket, unsigned int id, std::vector<std::shared_ptr<rtype::server::Lobby>> &lobbies);

            void start();

            void setLobby(const std::string &lobby);

            bool createLobby(const std::string &name);
            void getLobbies();
            bool joinLobby(const std::string &name);
            //bool quitLobby(const std::string &name);

            unsigned int getId() const
            {
                return _id;
            };

        private:

            void readClient();
            void writeToClient(const std::string &message);

            unsigned int _id;

            std::string _lobby;
            std::vector<std::shared_ptr<Lobby>> _lobbies;

            TCP::socket _socket;
            std::string _data;

    };

};

#endif /* !TCPCONNECTION_HPP_ */