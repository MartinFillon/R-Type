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

#include "Packet.hpp"

#include "Packet.hpp"

#define LOGIN 0x42
#define DATA_MAX_SIZE 1024

#define NEW_CLIENT(x) \
    "New client [" << x << "]" \
                   << " connected"

namespace Rtype {

    class Server;

    class Client {

        using Message = std::vector<uint8_t>;

        using Socket = asio::ip::udp::socket;
        using Endpoint = asio::ip::udp::endpoint;

      public:
        Client(const unsigned int id, Server &server, const Endpoint &endpoint, Socket &socket);

        void send(const Packet &packet);
        void disconnect();

      private:
        unsigned int _id;
        bool _running;

        Server &_server;
        Socket &_socket;
        Endpoint _endpoint;
    };

}; // namespace Rtype

#endif /* !CLIENT_HPP_ */
