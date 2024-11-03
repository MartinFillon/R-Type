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

#include "ComponentFactory.hpp"
#include "Packet.hpp"
#include "Protocol.hpp"
#include "Registry.hpp"

#define R_ERROR 84
#define SUCCESS 0

#define DATA_MAX_SIZE 1024
#define KEEPALIVE_TIMEOUT 1

namespace rtype::client {

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
        ~Network() = default;

        void setRegistry(std::shared_ptr<ecs::Registry> registry);

        void setFactory(std::shared_ptr<ecs::ComponentFactory> &factory)
        {
            _cf = factory;
        }

        int setup(const std::string &host, const std::string &port);

        int run();
        void updateRegistry(const protocol::Packet &received_packet);
        void send(const protocol::Packet &packet);
        void send(const uint8_t opcode, const Arguments &arguments = {});

        void stop();

      private:
        Context _context;
        Resolver _resolver;
        Endpoint _endpoint;

        Socket _socket;
        bool running = true;
        ecs::Clock _keepaliveClock;

        std::shared_ptr<ecs::Registry> _registry;
        std::shared_ptr<ecs::ComponentFactory> _cf;
        std::size_t _id;
        std::unordered_map<
            protocol::Operations,
            std::function<
                void(std::shared_ptr<ecs::Registry> &, const protocol::Packet &, std::shared_ptr<ecs::ComponentFactory> &)>>
            _updateRegistryFunctions;
    };

}; // namespace rtype::client
#endif /* !NETWORK_HPP_ */
