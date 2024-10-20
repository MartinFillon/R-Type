/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** StreetFighter
*/

#include <exception>
#include <iostream>
#include <cstdlib>

#include "../include/Game.hpp"
#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Gravitable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Life.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Entity.hpp"
#include "Systems/GravitableMouvementSystem.hpp"
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
    _r.register_if_not_exist<ecs::component::KeyPressed>();
    try {
        _r._entities.addEntity(_factory.createEntity("StreetFighter/config/Background.json"));
        _r._entities.addEntity(_factory.createEntity("StreetFighter/config/Ken.json"));
        _r.add_system(ecs::systems::GravitableMouvementSystem());
    } catch (const std::exception &e) {
        std::cout << "Setup error on: " << e.what() << "\n";
        return;
    }
}

ecs::Entity street_fighter::Game::findPlayerIndex()
{
    auto &animations = _r.get_components<ecs::component::Animations>();
    int idx = 0;

    for (auto &&[anim] : ecs::custom_zip(animations)) {
        if (!anim) {
            idx += 1;
            continue;
        }
        if (anim->_object == ecs::component::Player && anim->_type == ecs::component::Type::First) {
            break;
        }
        idx += 1;
    }

    return ecs::Entity(idx);
}

int street_fighter::Game::run()
{
    _r.run_systems(nullptr);
    return EXIT_SUCCESS;
}
