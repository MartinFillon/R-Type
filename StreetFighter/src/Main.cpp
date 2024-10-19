/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "../include/Game.hpp"
#include "Gui.hpp"

int main()
{
    street_fighter::Game game;
    street_fighter::Gui gui(game);

    return gui.run();
}
