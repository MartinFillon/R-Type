/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include <iostream>
#include "Gui.hpp"

int main()
{
    rtype::Gui gui;
    gui.run();
    if (gui.setupNetwork(server_ip, server_port)) {
        return 84;
    }
    return SUCCESS;
}
