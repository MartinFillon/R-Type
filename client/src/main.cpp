/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include "Gui.hpp"

int main(int ac, char **av)
{
    if (ac != NB_ARGS) {
        return ERROR;
    }

    rtype::Gui gui(av[HOST], av[PORT]);

    gui.getMenu().launchMenu();
    gui.run();
    return SUCCESS;
}
