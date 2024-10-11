/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <asio.hpp>
#include <memory>
#include <mutex>
#include <vector>
#include <unordered_map>

#include "Client.hpp"
#include "Clock.hpp"
#include "Game.hpp"
#include "INetwork.hpp"

#define PORT 1
#define NB_ARGS_REQUIRED 2

#define R_TYPE_ERROR 84
#define SUCCESS 0

#define SERVER_MISSING_PORT "Server cannot start: server port not specified"
#define SERVER_START(x) "Server started at port " << x << "..."
#define SERVER_STOP "Server stoped..."

#define MESSAGE_RECEIVED(x) "Message received from [" << x << "]"

#define FIRST_PLAYER_PLACE 0
#define MAX_PLAYER_PLACES 3

#define KEEPALIVE_TIMEOUT 2

namespace rtype::server {

    /// @brief Class of the server's context.
    class Server : public ecs::INetwork {

        using Message = std::vector<uint8_t>;
        using Client = std::shared_ptr<rtype::server::Client>;

        using Context = asio::io_context;
        using Socket = asio::ip::udp::socket;
        using Endpoint = asio::ip::udp::endpoint;

      public:
        /// @brief Generates a `Server` which is the context of the backend server of the game storing all the necessary
        /// data, the ECS's context, and the networking.
        /// @param port an `int` representing the port on which the server is listening.
        Server(int port);

        /// @brief Runs the server by launching the `start()` function of the server.
        /// @return Always `EXIT_SUCCESS` for now.
        int run(std::shared_ptr<ecs::IContext> &ctx) override;

        /// @brief Starts the server by setting up all the networking, the data with the global context, and creates the
        /// necessary threads.
        void start(std::shared_ptr<ecs::IContext> &ctx);

        /// @brief Stops the server by disconnecting all the clients and closing the networking.
        void stop();

        /// @brief Broadcasts the given `packet` to all the currently connected clients.
        /// @param packet a `const Packet &` representing the reference to the packet to be sent to all the currently
        /// connected clients.
        void broadcast(const ecs::Packet &packet) override;

        /// @brief Broadcasts the given `packet` to all the currently connected clients except one.
        /// @param client_id a `const unsigned int` representing the client's id which NOT sent the message.
        /// @param packet a `const Packet &` representing the reference to the packet to be sent to all the currently
        /// connected clients except client_id.
        void broadcastExcept(const unsigned int client_id, const ecs::Packet &packet);

        /// @brief Handles any message received by the server from any connected client.
        /// @param id a `const unsigned int` representing the client's id which sent the message.
        /// @param message a `Message &` aka `std::vector<uint8_t> &` representing the reference to the bitshifted
        /// message sent by the client.
        void handleMessage(const unsigned int id, const Message &message);

        /// @brief Transforms the `data` into its bitshifted version of `length` bits.
        /// @param length a `const int` representing the length of the bitshifted data in bits.
        /// @param data a `const unsigned int` representing the data to bitshift.
        /// @return `std::vector<uint8_t>` representing the bitshifted result of the given `data` by the given `length`.
        std::vector<uint8_t> getBitshiftedData(const int length, const unsigned int data);

      private:
        /// @brief Loops the main network loop by checking new clients connections and current ones too with new
        /// messages from clients.
        void acceptConnections();

        /// @brief Disconnects the client according to the given `client_id`.
        /// @param client_id a `const unsigned int` representing the id of the client to disconnect.
        void disconnectClient(const unsigned int client_id);

        /// @brief Loops the main game loop by updating the game state and broadcasting all the packets stored in the
        /// packet queue.
        /// @param ctx a `std::shared_ptr<ecs::IContext>` representing the reference to the global context of the
        void processGame(std::shared_ptr<ecs::IContext> ctx);

        /// @brief Sends the given `packet` to the client which has as its id `client_id`.
        /// @param client_id a `const unsigned int` representing the id of the client to send the given `packet`.
        /// @param packet a `const Packet &` representing the reference to the packet to send to the client.
        void sendToClient(const unsigned int client_id, const ecs::Packet &packet);

        /// @brief Deletes the client which has as its id `client_id`.
        /// @param client_id a `const unsigned int` representing the id of the client to delete.
        void removeClient(const unsigned int client_id);

        /// @brief Generates a hashed client id from the `endpoint` address and port.
        /// @param endpoint a `const Ednpoint &` aka `const asio::ip::udp::endpoint &` representing the reference to the
        /// server's UDP socket endpoint.
        /// @return `unsigned int` representing the newly created client id.
        unsigned int generateClientId(const Endpoint &endpoint);

        /// @brief Handles all the actions which can be called by the UDP clients.
        /// @param client_id a `const unsigned int` representing the id of the UDP client who called the event.
        /// @param packet a `const Packet &` representing the reference to the packet sent by the client.
        void processAction(const unsigned int client_id, const ecs::Packet &packet);

        /// @brief Handles all the events which can be called by the UDP clients.
        /// @param client_id a `const unsigned int` representing the id of the UDP client who called the event.
        /// @param packet a `const Packet &` representing the reference to the packet sent by the client.
        void handleEvents(const unsigned int client_id, const ecs::Packet &packet);

        /// @brief Checks if there is any unused player place.
        /// @return `int` between `FRIST_PLAYER_PLACE` and `MAX_PLAYER_PALCES` if there is an available place, else -1.
        int placeInPlayers();

        /// @brief Get a player's place from the given `client_id`.
        /// @param client_id an `int` representing the UDP client id of the player you want the place of.
        /// @return `int` representing the player's place between `FRIST_PLAYER_PLACE` and `MAX_PLAYER_PALCES` if
        /// client's player is found, -1 else.
        int getPlayerPlace(int client_id);

        /// @brief Count the number of the player stored in the game/registry
        /// @return the number of the current player in the game/registry
        int countCurrentPlayer();

        /// @brief The global context of the backend server.
        Context _context;

        /// @brief The ports on which the server is listening for new clients connections.
        int _port;
        /// @brief `true` if the server is connected and running, `false` otherwise.
        bool _running;
        ecs::Clock _clock;
        /// @brief The game wrapper.
        rtype::server::Game _game;

        /// @brief The server's asio UDP socket.
        Socket _socket;

        /// @brief The server's mutex for locking threads.
        std::mutex _mutex;
        /// @brief The map of the clients `Client` indexed by the clients ids.
        std::unordered_map<int, Client> _clients;
        /// @brief The map of the players UDP clients ids indexed by the players places.
        std::unordered_map<int, std::optional<int>> _players_clients_ids;
    };

}; // namespace rtype::server

#endif /* !SERVER_HPP_ */
