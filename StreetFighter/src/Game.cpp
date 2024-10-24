/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** StreetFighter
*/

#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>

#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Attributes.hpp"
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
#include "Game.hpp"
#include "Systems/BasicMouvementSystem.hpp"
#include "Systems/GravitableMouvementSystem.hpp"
#include "Systems/KickSystem.hpp"
#include "Systems/PunchSystem.hpp"
#include "ZipperIterator.hpp"

street_fighter::Game::Game()
{
    _r = std::make_shared<ecs::Registry>();
    _r->register_if_not_exist<ecs::component::Attributes>();
    _r->register_if_not_exist<ecs::component::Position>();
    _r->register_if_not_exist<ecs::component::Animations>();
    _r->register_if_not_exist<ecs::component::Drawable>();
    _r->register_if_not_exist<ecs::component::Controllable>();
    _r->register_if_not_exist<ecs::component::Sprite>();
    _r->register_if_not_exist<ecs::component::Size>();
    _r->register_if_not_exist<ecs::component::Destroyable>();
    _r->register_if_not_exist<ecs::component::Life>();
    _r->register_if_not_exist<ecs::component::Gravitable>();
    _r->register_if_not_exist<ecs::component::KeyPressed>();
    try {
        _factory.createEntity(_r, "StreetFighter/config/Background.json");
        _factory.createEntity(_r, "StreetFighter/config/Ken.json");
        _r->add_system(ecs::systems::GravitableMouvementSystem());
        _r->add_system(ecs::systems::BasicMouvementSystem());
        _r->add_system(ecs::systems::PunchSystem());
        _r->add_system(ecs::systems::KickSystem());
    } catch (const std::exception &e) {
        spdlog::error("Setup error on: [{}]", e.what());
        return;
    }
}

ecs::Entity street_fighter::Game::findPlayerIndex()
{
    auto &attributs = _r->get_components<ecs::component::Attributes>();
    int idx = 0;

    for (auto &&[atr] : ecs::custom_zip(attributs)) {
        if (!atr) {
            idx += 1;
            continue;
        }
        if (atr->_entity_type == ecs::component::Attributes::EntityType::Player &&
            atr->_ennemy_type == ecs::component::Attributes::EnnemyType::First) {
            break;
        }
        idx += 1;
    }

    return ecs::Entity(idx);
}

int street_fighter::Game::run()
{
    _r->run_systems(_factory, nullptr);
    return EXIT_SUCCESS;
}
