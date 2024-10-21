/*
** EPITECH PROJECT, 2024
** test
** File description:
** test
*/

#ifndef TEST_HPP_
    #define TEST_HPP_

#include <asio.hpp>
#include <memory>
#include <string>

using asio::ip::tcp;

class TCPCommunication : public std::enable_shared_from_this<TCPCommunication> {

    public:

        TCPCommunication(tcp::socket socket, int client_number);

        void start();
    private:
        void readClient();

        void writeToClient(const std::string &message);

        tcp::socket _socket;
        std::string _data;
        int _client_number;
};

class Network {

    public:

        Network(asio::io_context &io_context, short port);

    private:

        void acceptConnection();

        tcp::acceptor _acceptor;
        std::size_t _client_counter;
};


#endif /* !TEST_HPP_ */
