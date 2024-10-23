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

namespace client {
    class TCPCommunication {
        public:

            TCPCommunication(const std::string &host, const std::string &port);

            void run();
            void startGame();

        private:

            void readServ();
            void writeToServ();
            // void startDisplay(); à voir pour +

            asio::io_context _ioContext;
            asio::ip::tcp::socket _socket;
            asio::ip::tcp::resolver::results_type _endpoints;
            asio::streambuf _buff;

    };
}

#endif /* !TCPCommunication_HPP_ */
