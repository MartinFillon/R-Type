/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** StreetFighter
*/

#include <exception>
#include <iostream>
#include <cstdlib>

#include "../include/StreetFighter.hpp"
#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Gravitable.hpp"
#include "Components/Life.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "ZipperIterator.hpp"

street_fighter::Game::Game(): _factory(_r, ecs::ComponentFactory::Mode::Client)
{
    _r.register_if_not_exist<ecs::component::Position>();
    _r.register_if_not_exist<ecs::component::Animations>();
    _r.register_if_not_exist<ecs::component::Drawable>();
    _r.register_if_not_exist<ecs::component::Controllable>();
    _r.register_if_not_exist<ecs::component::Sprite>();
    _r.register_if_not_exist<ecs::component::Size>();
    _r.register_if_not_exist<ecs::component::Destroyable>();
    _r.register_if_not_exist<ecs::component::Life>();
    _r.register_if_not_exist<ecs::component::Gravitable>();
    try {
        _r._entities.addEntity(_factory.createEntity("StreetFighter/config/Ken.json"));
    } catch (const std::exception &e) {
        std::cout << e.what() << "\n";
        return;
    }
}

int street_fighter::Game::run()
{
    auto &positions = _r.get_components<ecs::component::Position>();
    auto &animations = _r.get_components<ecs::component::Animations>();

    for (auto &&[pos, anim] : ecs::custom_zip(positions, animations)) {
        std::cout << "pos x: " << pos->_x << " y: " << pos->_y << "\n";
        std::cout << "anim w: " << anim->_width << " h: " << anim->_height << " x: " << anim->_x << " y: " << anim->_y << " type: " << anim->_type << " obj: " << anim->_object << "\n";
    }

    return EXIT_SUCCESS;
}
