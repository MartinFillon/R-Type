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

namespace rtype::server {

    class Lobby;

    using TCP = asio::ip::tcp;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection> {

        public:

            TCPConnection(TCP::socket socket, std::vector<std::shared_ptr<rtype::server::Lobby>> &lobbies);

            void start();

            void setLobby(const std::string &lobby);

        private:

            void readClient();
            void writeToClient(const std::string &message);

            std::string _lobby;
            std::vector<std::shared_ptr<Lobby>> _lobbies;

            TCP::socket _socket;
            std::string _data;

    };

};

#endif /* !TCPCONNECTION_HPP_ */