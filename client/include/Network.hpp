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
#include "Protocol.hpp"
#include "Registry.hpp"

#define ERROR 84
#define SUCCESS 0

#define DATA_MAX_SIZE 1024
#define KEEPALIVE_TIMEOUT 1

namespace client {

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

        void setRegistry(std::shared_ptr<ecs::Registry> registry);

        int setup(const std::string &host, const std::string &port);

        int run();
        void updateRegistry(const ecs::Packet &received_packet);
        void send(const ecs::Packet &packet);
        void send(const uint8_t opcode, const Arguments &arguments = {});

      private:
        Context _context;
        Resolver _resolver;
        Endpoint _endpoint;

        Socket _socket;

        ecs::Clock _keepaliveClock;

        std::shared_ptr<ecs::Registry> _registry;
        std::size_t _id;
        std::unordered_map<
            protocol::Operations,
            std::function<void(std::shared_ptr<ecs::Registry> &, const ecs::Packet &)>>
            _updateRegistryFunctions;
    };

}; // namespace client

#endif /* !NETWORK_HPP_ */
