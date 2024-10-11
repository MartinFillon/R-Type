/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Main
*/

#include <memory>

#include <iostream>
#include "Context.hpp"
#include "INetwork.hpp"
#include "Server.hpp"

std::shared_ptr<ecs::INetwork> create_network(int port)
{
    return std::make_shared<rtype::server::Server>(port);
}

std::shared_ptr<ecs::IContext> create_context(std::shared_ptr<ecs::INetwork> &network)
{
    return std::make_shared<rtype::server::Context>(network);
}

int main(int ac, char **av)
{
    if (ac != NB_ARGS_REQUIRED) {
        std::cerr << SERVER_MISSING_PORT << std::endl;
        return R_TYPE_ERROR;
    }

    int port = std::stoi(av[PORT]);

    auto server = create_network(port);
    auto ctx = create_context(server);

    return server->run(ctx);
}
