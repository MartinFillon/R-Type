/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #include <asio.hpp>

    #include "Lobby.hpp"
    #include "IContext.hpp"
    #include "INetwork.hpp"
    #include "TCPConnection.hpp"

    #define NETWORK_START(x) "Server started at port " << x << "."
    #define DEFAULT_UDP_PORT 1234

namespace rtype::server {

    using TCP = asio::ip::tcp;

    class Network {

        public:

            Network(int port);

            void broadcast(const ecs::IPacket &packet) {(void)packet;};
            int run();
            unsigned int generateClientId(const TCP::endpoint &endpoint);

        private:

            int start();
            void acceptConnection();

            void runClient(TCP::socket socket);
    
            int _port;
            bool _running;

            int _udpPort;

            std::vector<Lobby> _lobbies;

            std::shared_ptr<ecs::IContext> _gameContext;

            std::vector<std::shared_ptr<TCPConnection>> _clients;
            std::vector<std::thread> _threads;

            asio::io_context _context;
            TCP::acceptor _acceptor;


    };

};

#endif /* !NETWORK_HPP_ */