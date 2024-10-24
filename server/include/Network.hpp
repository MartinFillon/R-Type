/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #include <asio.hpp>
#include <functional>

    #include "Lobby.hpp"
    #include "IContext.hpp"
    #include "INetwork.hpp"
    #include "TCPConnection.hpp"

    #define NETWORK_START(x) "Server started at port " << x << "."

namespace rtype::server {

    using TCP = asio::ip::tcp;

    class Network : public ecs::INetwork {

        public:

            Network(int port);

            void broadcast(const ecs::IPacket &packet) {(void)packet;};
            int run(std::shared_ptr<ecs::IContext> &context);
            unsigned int generateClientId(const TCP::endpoint &endpoint);

        private:

            int start(std::shared_ptr<ecs::IContext> &context);
            void acceptConnection();

            void runClient(TCP::socket socket);
    
            int _port;
            bool _running;

            std::vector<Lobby> _lobbies;

            std::vector<std::shared_ptr<TCPConnection>> _clients;
            std::vector<std::thread> _threads;

            asio::io_context _context;
            TCP::acceptor _acceptor;


    };

};

#endif /* !NETWORK_HPP_ */