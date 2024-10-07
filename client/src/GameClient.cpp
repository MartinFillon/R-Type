/*
** EPITECH PROJECT, 2024
** R type
** File description:
** Game file
*/

#include "GameClient.hpp"
#include "ComponentFactory.hpp"
#include "ImageResolver.hpp"
#include "Systems/BasicRandomEnnemiesSystem.hpp"
#include "Systems/CollisionsSystem.hpp"
#include "Systems/DestroySystem.hpp"
#include "Systems/EnnemiesMilespatesSystem.hpp"
#include "Systems/GunFireSystem.hpp"
#include "Systems/ParallaxSystem.hpp"
#include "Systems/PlayerMouvementSystem.hpp"
#include "ZipperIterator.hpp"

rtype::GameClient::GameClient(sf::RenderWindow &window, std::shared_ptr<ecs::Registry> r)
    : _r(std::make_shared<ecs::Registry>()), _gameWin(window)
{
    setupGame();
}

void rtype::GameClient::setupDestroy()
{
    _r->add_system(ecs::systems::DestroySystem());
}

void rtype::GameClient::setupWeapon()
{
    _r->add_system(ecs::systems::GunFireSystem());
}

void rtype::GameClient::setupPlayer()
{
    _factory.createEntity("config/player.json");
    _r->add_system(ecs::systems::PlayerMouvementSystem());
}

void rtype::GameClient::setupCollisons()
{
    _r->add_system(ecs::systems::CollisionsSystem());
}

void rtype::GameClient::setupBasicEnnemies()
{
    _r->add_system(ecs::systems::EnnemiesMilespatesSystem());
    _r->add_system(ecs::systems::BasicRandomEnnemiesSystem());
}

void rtype::GameClient::setupBackground()
{
    _factory.createEntity("config/background/background.json");
    _factory.createEntity("config/background/background_2.json");
    _factory.createEntity("config/background/background_3.json");
    _factory.createEntity("config/background/background_4.json");
    ecs::systems::ParalaxSystem parallaxSystem;
    _r->add_system(parallaxSystem);
}

void rtype::GameClient::setupGame()
{
    _factory = ecs::ComponentFactory(_r, ecs::ComponentFactory::Mode::Client);
    setupBackground();
    setupPlayer();
    setupWeapon();
    setupBasicEnnemies();
    setupCollisons();
    setupDestroy();
}

int rtype::GameClient::run()
{
    auto &drawables = _r->get_components<ecs::component::Drawable>();
    auto &sprites = _r->get_components<ecs::component::Sprite>();
    auto &positions = _r->register_component<ecs::component::Position>();
    auto &animations = _r->register_component<ecs::component::Animations>();
    auto &size = _r->register_component<ecs::component::Size>();
    int testTick(20);

    while (_gameWin.isOpen()) {
        sf::Event event;
        while (_gameWin.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _gameWin.close();
            }
        }
        if (_systemClock.getSeconds() > (1 / 5)) {
            _r->run_systems();
            _systemClock.restart();
        }
        if (_drawClock.getSeconds() > (1 / 60)) {
            _gameWin.clear();
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
                _gameWin.draw(sprite);
            }
            _drawClock.restart();
        }
        _gameWin.display();
    }
    _gameWin.clear();
    _r->run_systems();
    return SUCCESS;
}