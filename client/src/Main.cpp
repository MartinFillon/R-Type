/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include <spdlog/cfg/env.h>

#include "Gui.hpp"

// #include "TCPCommunication.hpp"

int main()
{
    spdlog::cfg::load_env_levels();
    rtype::client::Gui gui;

    return gui.run();
}
