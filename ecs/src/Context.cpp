/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Context
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Context.hpp"
#include "Components/Position.hpp"
#include "Components/Drawable.hpp"
#include "Components/Controllable.hpp"
#include "Components/Sprite.hpp"
#include "Components/Animations.hpp"
#include "Entity.hpp"

namespace ecs {

Context::Context(): _window(sf::VideoMode(1920, 1080), "R-Type"), _entitys()
{
}

void Context::setupPlayer()
{
    Entity player = _r.spawn_entity();
    _entitys.addEntity(player);

    auto &positions = _r.register_component<ecs::component::Position>();
    auto &drawables = _r.register_component<ecs::component::Drawable>();
    auto &controllable = _r.register_component<ecs::component::Controllable>();
    auto &sprite = _r.register_component<ecs::component::Sprite>();
    auto &animation = _r.register_component<ecs::component::Animations>();

    positions[player.getId()] = ecs::component::Position{100, 100};
    drawables[player.getId()] = ecs::component::Drawable{true};
    controllable[player.getId()] = ecs::component::Controllable{true, 0.2};
    sprite[player.getId()] = ecs::component::Sprite{"assets/sprites/r-typesheet42.gif"};
    animation[player.getId()] = ecs::component::Animations{35, 20, 0, 0};
}

void Context::setupBackground()
{
}

void Context::setup()
{
    setupPlayer();
    setupBackground();
}

int Context::run()
{
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
              _window.close();
        }
        _window.clear();
        _r.run_systems();


/*        if (drawables[entity.getId()]-> _drawable) {
            auto &pos = positions[entity.getId()];
            square.setPosition(pos->_x, pos->_y);
            _window.draw(square);
        }*/

        _window.display();
    }
    return EXIT_SUCCESS;
}

Context::~Context()
{
    return;
}

sf::RenderWindow &Context::getRenderWindow()
{
    return _window;
}

}
