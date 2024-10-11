/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Main
*/

#include <memory>
#include "Context.hpp"
#include "INetwork.hpp"
#include "Server.hpp"

int main(int ac, char **av)
{
    if (ac != NB_ARGS_REQUIRED) {
        std::cerr << SERVER_MISSING_PORT << std::endl;
        return R_TYPE_ERROR;
    }

    std::shared_ptr<ecs::INetwork> server = std::make_shared<ecs::INetwork>(rtype::Server(std::atoi(av[PORT])));

    rtype::Context ctx = rtype::Context(server);

    return server->run();
}
