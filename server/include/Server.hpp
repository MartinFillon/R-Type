/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <asio.hpp>
#include <mutex>
#include <vector>
#include <unordered_map>

#include "Client.hpp"
#include "Game.hpp"
#include "IContext.hpp"
#include "protocol.hpp"

#define PORT 1
#define NB_ARGS_REQUIRED 2

#define ERROR 84
#define SUCCESS 0

#define SERVER_MISSING_PORT "Server cannot start: server port not specified"
#define SERVER_START(x) "Server started at port " << x << "..."
#define SERVER_STOP "Server stoped..."

#define MESSAGE_RECEIVED(x) "Message received from [" << x << "]"

#define FIRST_PLAYER_PLACE 1
#define MAX_PLAYER_PLACES 4

namespace Rtype {

    class Server : ecs::IContext {

        using Message = std::vector<uint8_t>;
        using Client = std::shared_ptr<Rtype::Client>;

        using Context = asio::io_context;
        using Socket = asio::ip::udp::socket;
        using Endpoint = asio::ip::udp::endpoint;

      public:
        Server(int port);

        int run();
        void start();
        void stop();

        void broadcast(const Packet &packet);
        void handleMessage(const unsigned int id, const Message &message);

        std::vector<uint8_t> getBitshiftedData(const int length, const unsigned int data);

      private:
        void acceptConnections();
        void processGame();

        void sendToClient(const unsigned int client_id, const Packet &packet);
        void removeClient(const unsigned int client_id);

        unsigned int generateClientId(const Endpoint &endpoint);

        void processAction(const unsigned int id, const Packet &packet);
        void handleEvents(const unsigned int id, const Packet &packet);

        int placeInPlayers(void);
        int Server::getPlayerPlace(int client_id);

        Context _context;

        int _port;
        bool _running;

        Rtype::Game _game;

        Socket _socket;

        std::mutex _mutex;
        std::unordered_map<int, Client> _clients;
        /// @brief std::unordered_map containing the MAX_PLAYER_PLACES player client_id for the MAX_PLAYER_PLACES
        /// player places
        std::unordered_map<int, std::optional<int>> _players_clients_ids;
    };

}; // namespace Rtype

#endif /* !SERVER_HPP_ */
