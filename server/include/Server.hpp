/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include <mutex>
    #include <vector>
    #include <asio.hpp>
    #include <unordered_map>

    #include "Game.hpp"
    #include "Client.hpp"

    #define PORT 1
    #define NB_ARGS_REQUIRED 2

    #define ERROR 84
    #define SUCCESS 0

    #define SERVER_START(x) "Server started at port " << x << "..."
    #define SERVER_STOP "Server stoped..."

namespace Rtype {

    class Server {

        using Message = std::vector<uint8_t>;
        using Client = std::shared_ptr<Rtype::Client>;

        using Context = asio::io_context;
        using Socket = asio::ip::udp::socket;
        using Endpoint = asio::ip::udp::endpoint;

        public:

            Server(int port);

            void start();
            void stop();

            void broadcast(const Packet &packet);
            void handleMessage(const int id, const Message &message);

        private:

            void acceptConnections();
            void processGame();

            void sendToClient(const int id, const Packet &packet);
            void removeClient(const int id);

            int generateClientId(const Endpoint &endpoint);

            Context _context;

            int _port;
            bool _running;

            Rtype::Game _game;

            Socket _socket;

            std::mutex _mutex;
            std::unordered_map<int, Client> _clients;

    };

};

#endif /* !SERVER_HPP_ */
