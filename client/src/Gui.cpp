/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#include <iostream>

#include "Gui.hpp"
#include "ImageResolver.hpp"
#include "ZipperIterator.hpp"
#include "Systems/GunFireSystem.hpp"
#include "Systems/ParallaxSystem.hpp"
#include "Systems/CollisionsSystem.hpp"
#include "Systems/PlayerMouvementSystem.hpp"
#include "Systems/BasicRandomEnnemiesSystem.hpp"

rtype::Gui::Gui(const std::string &host, const std::string &port):
    ecs::IContext(),
    _network(host, port),
    _window(sf::VideoMode(1920, 1080), GAME_NAME),
    _r(std::make_shared<ecs::Registry>()),
    _factory(ecs::ComponentFactory(_r))
{
    setupBackground();
    setupPlayer();
    setupWeapon();
    setupBasicEnnemies();
    setupCollisons();
    _network.setRegistry(_r);
    _window.close();
}

void rtype::Gui::start()
{
    std::thread handleNetwork(&rtype::Network::run, std::ref(_network));
    //std::thread handleGame(&rtype::Gui::run, this);

    handleNetwork.join();
    //handleGame.join();
}

void rtype::Gui::setupWeapon()
{
    _r->add_system(ecs::systems::GunFireSystem());
}

void rtype::Gui::setupPlayer()
{
    _factory.createEntity("config/player.json");
    _r->add_system(ecs::systems::PlayerMouvementSystem());
}

void rtype::Gui::setupCollisons()
{
    _r->add_system(ecs::systems::CollisionsSystem());
}

void rtype::Gui::setupBackground()
{
    _factory.createEntity("config/background/background.json");
    _factory.createEntity("config/background/background_2.json");
    _factory.createEntity("config/background/background_3.json");
    _factory.createEntity("config/background/background_4.json");
    _r->add_system(ecs::systems::ParalaxSystem());
}

void rtype::Gui::setupBasicEnnemies()
{
    _r->add_system(ecs::systems::BasicRandomEnnemiesSystem());
}

int rtype::Gui::run()
{
    auto &drawables = _r->get_components<ecs::component::Drawable>();
    auto &sprites = _r->get_components<ecs::component::Sprite>();
    auto &positions = _r->register_component<ecs::component::Position>();
    auto &animations = _r->register_component<ecs::component::Animations>();
    auto &size = _r->register_component<ecs::component::Size>();

    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }
        _window.clear();
        _r->run_systems();

        for (auto &&[draws, anim, spri, si, pos] :
                ecs::custom_zip(drawables, animations, sprites, size, positions)) {
            if (!draws || !anim || !spri || !si || !pos) {
                continue;
            }
            sf::Texture texture;
            ecs::ImageResolver image(PATH_TO_ASSETS);
            std::string pathToImage = image.getImage(spri->_pathToSprite);
            if (pathToImage.empty()) {
                continue;
            }
            texture.loadFromMemory(
                pathToImage.c_str(),
                pathToImage.size(),
                sf::IntRect(anim->_x, anim->_y, anim->_width, anim->_height)
            );
            sf::Sprite sprite;
            sprite.setPosition(pos->_x, pos->_y);
            sprite.setScale(si->_width, si->_height);
            sprite.setTexture(texture);
            _window.draw(sprite);
        }
        _window.display();
    }
    return SUCCESS;
}
