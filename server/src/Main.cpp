/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Main
*/

#include "Server.hpp"

int main(int ac, char **av)
{
    Rtype::Server server(4242);

    server.start();

    return SUCCESS;
}