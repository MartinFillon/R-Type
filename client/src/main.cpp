/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include "Gui.hpp"

int main()
{
    rtype::Gui gui;
    std::string server_address = gui.getMenu().launchMenu();
    std::string server_ip = server_address.substr(0, server_address.find(':'));
    std::string server_port = server_address.substr(server_address.find(':') + 1);

    if (gui.setupNetwork(server_ip, server_port)) {
        return 84;
    }

    std::thread network = std::thread(&rtype::Gui::runNetwork, std::ref(gui));

    gui.run();

    network.join();

    return SUCCESS;
}
