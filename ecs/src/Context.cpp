/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Context
*/

#include <functional>
#include <iostream>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Context.hpp"
#include "Entity.hpp"
#include "ImageResolver.hpp"

#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Sprite.hpp"

#include "Systems/PlayerMouvementSystem.hpp"

namespace ecs {

Context::Context() : _window(sf::VideoMode(1920, 1080), "R-Type"), _entitys() {}

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
    sprite[player.getId()] = ecs::component::Sprite{"r-typesheet42.gif"};
    animation[player.getId()] = ecs::component::Animations{35, 20, 0, 0};

    ecs::systems::PlayerMouvementSystem playerMovementSystem;
    _r.add_system(playerMovementSystem);
}

void Context::setupBackground() {}

void Context::setup()
{
    setupPlayer();
    setupBackground();
}

int Context::run()
{
    this->setup();
    auto &drawables = _r.get_components<ecs::component::Drawable>();
    auto &sprites = _r.get_components<ecs::component::Sprite>();
    auto &positions = _r.register_component<ecs::component::Position>();
    auto &animations = _r.register_component<ecs::component::Animations>();

    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _window.clear();
        _r.run_systems();

        for (std::size_t i = 0; i < _entitys.size(); ++i) {
            if (drawables[i]->_drawable) {
                sf::Texture texture;
                if (sprites[i] && animations[i]) {
                    ImageResolver image("assets/sprites/");
                    std::string pathToImage = image.getImage(sprites[i]->_pathToSprite);
                    texture.loadFromMemory(
                        pathToImage.c_str(),
                        pathToImage.size(),
                        sf::IntRect(animations[i]->_x, animations[i]->_y, animations[i]->_width, animations[i]->_height)
                    );
                }
                sf::Sprite sprite;
                sprite.setPosition(positions[i]->_x, positions[i]->_y);
                sprite.setTexture(texture);
                _window.draw(sprite);
            }
        }
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

} // namespace ecs
