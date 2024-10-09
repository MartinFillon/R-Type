/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <asio.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "Clock.hpp"
#include "Packet.hpp"

#define LOGIN 0x42
#define DATA_MAX_SIZE 1024

#define NEW_CLIENT(x) "New client [" << x << "]" << " connected"
#define CLIENT_LEFT(x) "Client [" << x << "]" << " disconnected"

namespace rtype {

    class Server;

    /// @brief Class to wrap all the utilities of the clients networking and logic.
    class Client {

        using Message = std::vector<uint8_t>;

        using Socket = asio::ip::udp::socket;
        using Endpoint = asio::ip::udp::endpoint;

      public:
        /// @brief Generates a `Client` storing its connection entry point, id, and all necessary data to communicate
        /// later.
        /// @param client_id a `const unsigned int` representing the client's UDP id.
        /// @param server a `Server &` representing the reference to the wrapper of the whole server.
        /// @param endpoint a `const Endpoint &` aka `const asio::ip::udp::endpoint &` representing the reference to the
        /// UDP socket endpoint.
        /// @param socket a `const Socket &` aka `const asio::ip::udp::socket &` representing the reference to the
        /// server's asio UDP socket.
        Client(const unsigned int client_id, Server &server, const Endpoint &endpoint, Socket &socket);

        /// @brief Sends the given `packet` to the client via its UDP socket.
        /// @param packet a `const Packet &` representing to packet to send to the client.
        void send(const Packet &packet);
        /// @brief Disconnects the client from the server.
        void disconnect();
        /// @brief Checks if the client is running or not.
        /// @return `true` if the client is running or `false` if not.
        bool isRunning();
        /// @brief Get the client's heartbeat clock.
        /// @return `ecs::Clock &` representing the client's heartbeat clock.
        ecs::Clock &getHeartbeatClock();

      private:
        /// @brief The client's UDP id.
        unsigned int _id;
        /// @brief `true` if the client is connected and running, `false` otherwise.
        bool _running;
        /// @brief The client's heartbeat clock to know since when the server received the last
        /// `protocol::Operations::PING` packet.
        ecs::Clock _heartbeatClock;

        /// @brief The reference to the wrapper of the whole server.
        Server &_server;
        /// @brief The reference to the server's asio UDP socket.
        Socket &_socket;
        /// @brief The reference to the UDP socket endpoint.
        Endpoint _endpoint;
    };

}; // namespace rtype

#endif /* !CLIENT_HPP_ */
