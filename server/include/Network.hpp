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

namespace rtype::server {

    using TCP = asio::ip::tcp;

    class Network : public ecs::INetwork {

        public:

            Network(int port);

            void broadcast(const ecs::IPacket &packet) {(void)packet;};
            int run(std::shared_ptr<ecs::IContext> &context);
    

        private:

            int start(std::shared_ptr<ecs::IContext> &context);
            void acceptConnection();
    
            int _port;
            bool _running;

            std::vector<std::shared_ptr<Lobby>> _lobbies;

            asio::io_context _context;
            TCP::acceptor _acceptor;


    };

};

#endif /* !NETWORK_HPP_ */