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
#include "asio/error_code.hpp"

rtype::client::TCPCommunication::TCPCommunication(): _port(0), _ioContext(), _socket(_ioContext) {}

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
    asio::error_code error;
    asio::read_until(_socket, _buffer, '\n', error);

    if (error) {
        std::cerr << error.message() << std::endl;
    }

    std::istream is(&_buffer);
    std::string line;
    std::getline(is, line);
    if (line[0] == '\0') {
        line.erase(0, 1);
    }
    if (line.find("UDP") != std::string::npos) {
        _port = std::stoi(line.substr(line.find(':') + 1));
    }
    return line;
}

void rtype::client::TCPCommunication::send(const std::string &data)
{
    asio::error_code error;
    asio::write(_socket, asio::buffer(data), error);

    if (error) {
        std::cerr << error.message() << std::endl;
    }
}
