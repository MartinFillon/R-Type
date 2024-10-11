/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #include <memory>
    #include <asio.hpp>

    #include "Packet.hpp"
    #include "Registry.hpp"
    #include "Protocol.hpp"
    #include "Components/Position.hpp"

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
            void updateRegistry(const rtype::Packet &received_packet);
            void send(const rtype::Packet &packet);
            void send(const uint8_t opcode, const Arguments &arguments = {});

        private:

            Context _context;
            Resolver _resolver;
            Endpoint _endpoint;

            Socket _socket;

            ecs::Clock _keepaliveClock;

            std::shared_ptr<ecs::Registry> _registry;
            std::size_t _id;
            std::unordered_map<protocol::Operations, std::function<void(std::shared_ptr<ecs::Registry> &, const rtype::Packet &)>> _updateRegistryFunctions;

    };

};

#endif /* !NETWORK_HPP_ */
