/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** TCPConnection class
*/

#ifndef TCPCOMMUNICATION_HPP_
    #define TCPCOMMUNICATION_HPP_

    #include <asio.hpp>
    #include <string>

    #define ERROR 84
    #define SUCCESS 0

namespace rtype::client {
    class TCPCommunication {
        public:

            TCPCommunication();

            int setup(const std::string &host, const std::string &port);

            void run();
            void startGame();

            void send(const std::string &data);
            std::string read();

        private:

            asio::io_context _ioContext;
            asio::ip::tcp::socket _socket;
            asio::ip::tcp::resolver::results_type _endpoints;

    };
}

#endif /* !TCPCommunication_HPP_ */
