/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Network
*/

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include "asio/buffer.hpp"
#include "asio/read.hpp"
#include "asio/write.hpp"
#include "asio/error_code.hpp"
#include "asio/read_until.hpp"

#include "TCPConnection.hpp"

rtype::server::TCPConnection::TCPConnection(TCP::socket socket, unsigned int id, std::vector<Lobby> &lobbies): _socket(std::move(socket)), _id(id), _lobbies(lobbies)
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
    while (true) {

        asio::error_code error;
        size_t length = asio::read_until(_socket, asio::dynamic_buffer(_data), '\n', error);

        if (error) {
            continue;
        }

        std::string message = _data.substr(0, length - 1);

        if (message.find("CREATE") != std::string::npos) {
            createLobby(message.substr(7));
        }
        if (message.find("LIST") != std::string::npos) {
            dumpLobbies();
        }
        if (message.find("JOIN") != std::string::npos) {
            joinLobby(message.substr(5));
        }
        if (message.find("QUIT") != std::string::npos) {
            quitLobby(message.substr(5));
        }

        _data.clear();

    }
}

bool rtype::server::TCPConnection::createLobby(const std::string &name)
{
    if (_lobbies.size() == MAX_LOBBIES) {
        writeToClient("Too many lobbies created.");
        return false;
    }

    for (auto &lobby: _lobbies) {
        if (lobby.getName() == name) {
            writeToClient("Name already used.");
            return false;
        }
    }

    _lobbies.push_back(Lobby(name));

    writeToClient("Lobby: " + name + " created!");

    return true;
}

void rtype::server::TCPConnection::dumpLobbies()
{
    if (_lobbies.empty()) {
        writeToClient("No current lobbies");
        return;
    }
    for (auto &lobby: _lobbies) {
        writeToClient(lobby.getName() + " => " + std::to_string(lobby.getNumberConnections()) + " / 4");
    }
}

bool rtype::server::TCPConnection::joinLobby(const std::string &name)
{
    if (!_lobby.empty()) {
        writeToClient("No lobbby.");
        return false;
    }

    for (auto &lobby: _lobbies) {
        if (lobby.getName() == name) {
            if (!lobby.assign(_id)) {
                writeToClient("Lobby is full.");
                return false;
            }
            writeToClient("Join successfully.");
            setLobby(name);
            return true;
        }
    }
    writeToClient("Lobby not found.");
    return false;
}

bool rtype::server::TCPConnection::quitLobby(const std::string &name)
{
    if (_lobby.empty()) {
        writeToClient("You're not in this lobby");
        return false;
    }

    for (auto &lobby: _lobbies) {
        if (lobby.getName() == name) {
            if (!lobby.unassign(_id)) {
                writeToClient("You're not in this lobby.");
                return false;
            }
            writeToClient("You quit lobby: " + name);
            setLobby("");
            return true;
        }
    }
    writeToClient("Lobby not found.");
    return false;
}

void rtype::server::TCPConnection::writeToClient(const std::string &message)
{
    asio::write(_socket, asio::buffer(message + "\n"));
}
