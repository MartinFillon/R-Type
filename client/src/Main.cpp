/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include "Gui.hpp"
//#include "TCPCommunication.hpp"

int main()
{
    //client::TCPCommunication tcp("127.0.0.1", "4242");
    // on va mettre un port en dure au debut pour le TCP (change après crea lobby et autre)
    //tcp.run();

    rtype::client::Gui gui;

    return gui.run();
}
