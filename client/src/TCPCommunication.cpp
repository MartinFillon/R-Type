/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** tcp connection file
*/

#include <cstdlib>
#include <iostream>
#include <spdlog/spdlog.h>

#include "TCPCommunication.hpp"
#include "asio/buffer.hpp"
#include "asio/read.hpp"
#include "asio/error_code.hpp"

rtype::client::TCPCommunication::TCPCommunication(): _ioContext(), _socket(_ioContext) {}

int rtype::client::TCPCommunication::setup(const std::string &host, const std::string &port)
{
    try {

        asio::ip::tcp::resolver resolver(_ioContext);
        _endpoints = resolver.resolve(host, port);

        _socket = asio::ip::tcp::socket(_ioContext);
        asio::connect(_socket, _endpoints);

        std::cout << read() << "\n";

    } catch (const std::exception &e) {
        spdlog::error("{}", e.what());
        return ERROR;
    }

    return SUCCESS;
}

std::string rtype::client::TCPCommunication::read()
{
    std::string data;
    asio::error_code error;
    size_t length = asio::read_until(_socket, asio::dynamic_buffer(data), '\n', error);

    if (error) {
        std::cerr << error.message() << std::endl;
    }

    std::cout << "data received: [" << data << "]" << std::endl;
    std::cout << "data received after: " << data.substr(0, length - 1) << std::endl;
    return data.substr(0, length - 1);
}

void rtype::client::TCPCommunication::send(const std::string &data)
{
    asio::error_code error;
    asio::write(_socket, asio::buffer(data), error);

    if (error) {
        std::cerr << error.message() << std::endl;
    }
}
