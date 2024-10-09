/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <asio.hpp>
#include <memory>

#include "Packet.hpp"
#include "Registry.hpp"

#define DATA_MAX_SIZE 1024

#define KEEPALIVE_TIMEOUT 1

namespace rtype {

    class Network {

        using UDP = asio::ip::udp;
        using Resolver = UDP::resolver;
        using Endpoint = UDP::endpoint;
        using Socket = UDP::socket;
        using Context = asio::io_context;

        using Message = std::vector<uint8_t>;
        using Arguments = std::vector<uint8_t>;

      public:
        Network();

        int setup(const std::string host, const std::string port);

        int run();

        void send(const Packet &packet);
        void send(const Message &message);
        void send(const uint8_t opcode, const Arguments &arguments = {});

      private:
        Context _context;
        Resolver _resolver;
        Endpoint _endpoint;

        Socket _socket;

        ecs::Clock _keepaliveClock;
    };

}; // namespace rtype

#endif /* !NETWORK_HPP_ */
