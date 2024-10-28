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

rtype::server::TCPConnection::TCPConnection(TCP::socket socket, unsigned int id, std::vector<Lobby> &lobbies, int port): _socket(std::move(socket)), _connected(true), _id(id), _ready(false), _port(port), _lobbies(lobbies)
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
    while (_connected) {

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
        if (message.find("UNREADY") != std::string::npos) {
            unready();
        } else if (message.find("READY") != std::string::npos) {
            ready();
        }
        if (message.find("START") != std::string::npos) {
            startLobby();
        }

        _data.clear();

    }
}

bool rtype::server::TCPConnection::createLobby(const std::string &name)
{
    if (_lobbies.size() == MAX_LOBBIES) {
        writeToClient("400: Too many lobbies created.");
        return false;
    }

    if (name.find(':') != std::string::npos) {
        writeToClient("400: No ':' on the name please.");
        return false;
    }

    for (auto &lobby: _lobbies) {
        if (lobby.getName() == name) {
            writeToClient("400: Name already used.");
            return false;
        }
    }

    _lobbies.push_back(Lobby(name, _port));

    writeToClient("200: Lobby: " + name + " created!");

    return true;
}

void rtype::server::TCPConnection::dumpLobbies()
{
    for (auto &lobby: _lobbies) {
        asio::write(_socket, asio::buffer(lobby.getName() + ":" + std::to_string(lobby.isRunning()) + ":" + std::to_string(lobby.getNumberConnections()) + ":" + std::to_string(lobby.getNumberReady()) + "\n"));
    }
    asio::write(_socket, asio::buffer("200\n"));
}

bool rtype::server::TCPConnection::joinLobby(const std::string &name)
{
    if (!_lobby.empty()) {
        writeToClient("400: No lobbby.");
        return false;
    }

    for (auto &lobby: _lobbies) {
        if (lobby.getName() == name) {
            if (!lobby.assign(*this)) {
                writeToClient("400: Lobby is full.");
                return false;
            }
            writeToClient("200: Join successfully.");
            setLobby(name);
            _ready = false;
            return true;
        }
    }
    writeToClient("400: Lobby not found.");
    return false;
}

bool rtype::server::TCPConnection::quitLobby(const std::string &name)
{
    if (_lobby.empty()) {
        writeToClient("400: You're not in this lobby");
        return false;
    }

    for (auto &lobby: _lobbies) {
        if (lobby.getName() == name) {
            if (!lobby.unassign(*this)) {
                writeToClient("400: You're not in this lobby.");
                return false;
            }
            writeToClient("200: You quit lobby: " + name);
            setLobby("");
            _ready = false;
            return true;
        }
    }
    writeToClient("400: Lobby not found.");
    return false;
}

bool rtype::server::TCPConnection::ready()
{
    if (_lobby.empty()) {
        writeToClient("400: You are not in a lobby.");
        return false;
    }

    if (_ready) {
        writeToClient("400: Already ready.");
        return false;
    }

    _ready = true;

    writeToClient("200: Ready!");
    return true;
}

bool rtype::server::TCPConnection::unready()
{
    if (_lobby.empty()) {
        writeToClient("400: You are not in a lobby.");
        return false;
    }

    if (!_ready) {
        writeToClient("400: You are not ready.");
        return false;
    }

    _ready = false;

    writeToClient("200: Not ready!");
    return true;
}

bool rtype::server::TCPConnection::startLobby()
{
    for (auto &lobby: _lobbies) {
        if (lobby.getName() == _lobby) {
            if (!lobby.start()) {
                writeToClient("400: All clients are not ready.");
                return false;
            }
            return true;
        }

    }

    writeToClient("400: You are not in a lobby.");
    return false;
}

void rtype::server::TCPConnection::writeToClient(const std::string &message)
{
    asio::write(_socket, asio::buffer(message + "\n"));
}
