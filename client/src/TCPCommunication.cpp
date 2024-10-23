/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** tcp connection file
*/

#include "TCPCommunication.hpp"
#include "asio/buffer.hpp"
#include <iostream>

client::TCPCommunication::TCPCommunication(const std::string &host, const std::string &port)
    : _socket(_ioContext)
{
    asio::ip::tcp::resolver resolver(_ioContext);
    _endpoints = resolver.resolve(host, port);
    asio::connect(_socket, _endpoints);
}

void client::TCPCommunication::run()
{
    //std::thread reader(&Zappy::Client::readServ, this);
    readServ();
    //reader.join();
    //display.join();
}

void client::TCPCommunication::startGame()
{
    //siwth au jeu ou, on peut fiare de la transition ici.
}

void client::TCPCommunication::readServ()
{
      try {
          std::istream is(&_buff);
          while (true) {
              asio::error_code error;
              asio::read_until(_socket, _buff, '\n', error);
              if (error == asio::error::eof) {
                  exit(EXIT_SUCCESS);
              }
              if (error) {
                  throw asio::system_error(error);
              }
              std::string line;
              std::getline(is, line);
              if (!line.empty() && line.back() == '\r') {
                  line.pop_back();
              }
              if (!line.compare("Welcome!")) {
                //writeToServ();
                asio::write(_socket, asio::buffer("CREATE tim\n"));
              }
          }
      } catch (std::exception &e) {
          std::cerr << e.what() << "\n";
      }
}

void client::TCPCommunication::writeToServ()
{
    while (true) {

        std::string command;
        std::getline(std::cin, command);
        if (command.empty()) {
            continue;
        }
        command += "\n";
        asio::write(_socket, asio::buffer(command));
    }
}