/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Client
*/

#include "Game.hpp"

Rtype::Game::Game() : _r(std::make_shared<ecs::Registry>()) {}

void Rtype::Game::update() {}

void Rtype::Game::handleLeaving(const unsigned int id)
{
    _r->_entities.erase(id);
}
