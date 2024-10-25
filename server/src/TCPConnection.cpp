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

rtype::server::TCPConnection::TCPConnection(TCP::socket socket, unsigned int id, std::vector<Lobby> &lobbies): _socket(std::move(socket)), _id(id), _ready(false), _lobbies(lobbies)
{
}

void rtype::server::TCPConnection::start(std::shared_ptr<ecs::IContext> &context)
{
    _gameContext = std::move(context);
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
        if (message.find("READY") != std::string::npos) {
            ready();
        }
        if (message.find("UNREADY") != std::string::npos) {
            unready();
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
        writeToClient("Too many lobbies created.");
        return false;
    }

    if (name.find(':') != std::string::npos) {
        writeToClient("No ':' on the name please.");
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
    for (auto &lobby: _lobbies) {
        asio::write(_socket, asio::buffer(lobby.getName() + ":" + std::to_string(lobby.isRunning()) + ":" + std::to_string(lobby.getNumberConnections()) + "\n"));
    }
    asio::write(_socket, asio::buffer("200\n"));
}

bool rtype::server::TCPConnection::joinLobby(const std::string &name)
{
    if (!_lobby.empty()) {
        writeToClient("No lobbby.");
        return false;
    }

    for (auto &lobby: _lobbies) {
        if (lobby.getName() == name) {
            if (!lobby.assign(*this)) {
                writeToClient("Lobby is full.");
                return false;
            }
            writeToClient("Join successfully.");
            setLobby(name);
            _ready = false;
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
            if (!lobby.unassign(*this)) {
                writeToClient("You're not in this lobby.");
                return false;
            }
            writeToClient("You quit lobby: " + name);
            setLobby("");
            _ready = false;
            return true;
        }
    }
    writeToClient("Lobby not found.");
    return false;
}

bool rtype::server::TCPConnection::ready()
{
    if (_lobby.empty()) {
        writeToClient("You are not in a lobby.");
        return false;
    }

    if (_ready) {
        writeToClient("Already ready.");
        return false;
    }

    _ready = true;

    writeToClient("Ready!");
    return true;
}

bool rtype::server::TCPConnection::unready()
{
    if (_lobby.empty()) {
        writeToClient("You are not in a lobby.");
        return false;
    }

    if (!_ready) {
        writeToClient("You are not ready.");
        return false;
    }

    _ready = false;

    writeToClient("Not ready!");
    return true;
}

bool rtype::server::TCPConnection::startLobby()
{
    for (auto &lobby: _lobbies) {
        if (lobby.getName() == _lobby) {
            if (!lobby.start(_gameContext)) {
                writeToClient("All clients are not ready.");
                return false;
            }
            return true;
        }

    }

    writeToClient("You are not in a lobby.");
    return false;
}

void rtype::server::TCPConnection::writeToClient(const std::string &message)
{
    asio::write(_socket, asio::buffer(message + "\n"));
}
