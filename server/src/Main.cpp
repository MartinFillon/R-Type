/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Main
*/

#include "Server.hpp"

int main(int ac, char **av)
{
    if (ac != NB_ARGS_REQUIRED) {
        return ERROR;
    }

    Rtype::Server server(std::atoi(av[PORT]));

    server.start();

    return SUCCESS;
}
