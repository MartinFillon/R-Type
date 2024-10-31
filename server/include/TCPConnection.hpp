/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** TCPconnection
*/

#ifndef TCPCONNECTION_HPP_
#define TCPCONNECTION_HPP_

#include <asio.hpp>
#include <functional>

#include "Lobby.hpp"
#include <unordered_map>

#define MAX_LOBBIES 4

namespace rtype::server {

    class Lobby;

    using TCP = asio::ip::tcp;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection> {

      public:
        TCPConnection(TCP::socket socket, unsigned int id, std::vector<Lobby> &lobbies, int port);

        void start();

        void setLobby(const std::string &lobby);

        bool createLobby(const std::string &name);
        bool joinLobby(const std::string &name);
        bool quitLobby(const std::string &name);
        bool startLobby();
        bool ready();
        bool unready();

        void dumpLobbies();

        unsigned int getId() const
        {
            return _id;
        };

        bool isReady() const
        {
            return _ready;
        };

        void setConnected(bool connected)
        {
            _connected = connected;
        };

        void writeToClient(const std::string &message);

      private:
        void readClient();

        bool _connected;

        unsigned int _id;
        bool _ready;

        int _port;

        std::string _lobby;
        std::vector<Lobby> &_lobbies;

        TCP::socket _socket;
        std::string _data;
    };

}; // namespace rtype::server

#endif /* !TCPCONNECTION_HPP_ */
