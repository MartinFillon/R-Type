/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Main
*/

#include <memory>
#include <spdlog/cfg/env.h>
#include <spdlog/spdlog.h>

#include "Network.hpp"
#include "Server.hpp"

int main(int ac, char **av)
{
    spdlog::cfg::load_env_levels();

    if (ac != NB_ARGS_REQUIRED) {
        spdlog::error("{}", SERVER_MISSING_PORT);
        return R_TYPE_ERROR;
    }
    std::shared_ptr<rtype::server::Network> server;

    int port = std::stoi(av[PORT]);

    try {
        server = std::make_shared<rtype::server::Network>(port);
    } catch (const std::exception &e) {
        spdlog::error("{}", e.what());
        return R_TYPE_ERROR;
    }

    return server->run();
}
