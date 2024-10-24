/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Main
*/

#include <memory>
#include <spdlog/cfg/env.h>
#include <spdlog/spdlog.h>

#include "Context.hpp"
#include "INetwork.hpp"
#include "Network.hpp"
#include "Server.hpp"

std::shared_ptr<ecs::INetwork> create_network(int port)
{
    return std::make_shared<rtype::server::Network>(port);
}

std::shared_ptr<ecs::IContext> create_context(std::shared_ptr<ecs::INetwork> &network)
{
    return std::make_shared<rtype::server::Context>(network);
}

int main(int ac, char **av)
{
    spdlog::cfg::load_env_levels();

    if (ac != NB_ARGS_REQUIRED) {
        spdlog::error("{}", SERVER_MISSING_PORT);
        return R_TYPE_ERROR;
    }
    std::shared_ptr<ecs::INetwork> server;
    std::shared_ptr<ecs::IContext> ctx;

    int port = std::stoi(av[PORT]);

    try {
        server = create_network(port);
        ctx = create_context(server);
    } catch (const std::exception &e) {
        spdlog::error("{}", e.what());
        return R_TYPE_ERROR;
    }

    return server->run(ctx);
}
