/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include <filesystem>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

#include "Poc.hpp"

int main(void)
{
    spdlog::cfg::load_env_levels();

    try {
        poc::Poc game(60);
        SetTraceLogLevel(LOG_ERROR); 
        return game.run();
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}