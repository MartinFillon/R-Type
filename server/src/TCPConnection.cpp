/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Network
*/

#include <iostream>
#include <string>
#include <variant>

#include "TCPConnection.hpp"

rtype::server::TCPConnection::TCPConnection(TCP::socket socket, std::vector<std::shared_ptr<Lobby>> &lobbies): _socket(std::move(socket)), _lobbies(lobbies)
{
}

void rtype::server::TCPConnection::start()
{
    readClient();
}

void rtype::server::TCPConnection::setLobby(const std::string &lobby)
{
    _lobby = lobby;
}

void rtype::server::TCPConnection::readClient()
{
    auto self(shared_from_this());

    asio::async_read_until(
        _socket,
        asio::dynamic_buffer(_data),
        '\n',
        [this, self](std::error_code ec, std::size_t length) {

            if (!ec) {

                std::string message = _data.substr(0, length - 1);

                if (message.find("CREATE") != std::string::npos) {
                    createLobby(message.substr(7));
                }

                if (message.find("LIST") != std::string::npos) {
                    getLobbies();
                }

            } else {
                std::cerr << ec.message() << std::endl;
            }

        }
    );
}

bool rtype::server::TCPConnection::createLobby(const std::string &name)
{
    if (_lobbies.size() == MAX_LOBBIES) {
        writeToClient("Too many lobbies created.");
        return false;
    }

    for (auto &lobby: _lobbies) {
        if (lobby->getName() == name) {
            writeToClient("Name already used.");
            return false;
        }
    }

    _lobbies.push_back(std::make_shared<Lobby>(name));

    writeToClient("Lobby: " + name + " created!" + std::to_string(_lobbies.size()));

    return true;
}

void rtype::server::TCPConnection::getLobbies()
{
    for (auto &lobby: _lobbies) {
        writeToClient(lobby->getName() + " => " + std::to_string(lobby->getNumberConnections()) + " / 4");
    }
}

void rtype::server::TCPConnection::writeToClient(const std::string &message)
{
    auto self(shared_from_this());

    asio::async_write(_socket, asio::buffer(message + "\n"), [this, self](std::error_code ec, std::size_t) {
        if (!ec) {
            _data.clear();
            readClient();
        } else {
            std::cerr << "Erreur d'écriture: " << ec.message() << std::endl;
            _socket.close();
        }
    });
}
