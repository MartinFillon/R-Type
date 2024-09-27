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

#include "Components/Parallax.hpp"
#include "Context.hpp"
#include "Entity.hpp"
#include "ImageResolver.hpp"

#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"

#include "Systems/ParallaxSystem.hpp"
#include "Systems/PlayerMouvementSystem.hpp"
#include "Systems/GunFireSystem.hpp"

namespace ecs {

    Context::Context() : _window(sf::VideoMode(1920, 1080), GAME_NAME), _entitys() {}

    void Context::setupWeapon()
    {
        Entity weapon = _r.spawn_entity();
        _entitys.addEntity(weapon);
        auto &positions = _r.register_component<ecs::component::Position>();
        auto &drawables = _r.register_component<ecs::component::Drawable>();
        auto &controllable = _r.register_component<ecs::component::Controllable>();
        auto &sprite = _r.register_component<ecs::component::Sprite>();
        auto &animation = _r.register_component<ecs::component::Animations>();
        auto &size = _r.register_component<ecs::component::Size>();

        positions[weapon.getId()] = ecs::component::Position{100, 100};
        drawables[weapon.getId()] = ecs::component::Drawable{false};
        controllable[weapon.getId()] = ecs::component::Controllable{true, 1.3};
        sprite[weapon.getId()] = ecs::component::Sprite{WEAPON_SPRITE};
        animation[weapon.getId()] = ecs::component::Animations{sf::Clock(), 18, 12, 0, 0, 0, ecs::component::Object::Weapon};
        size[weapon.getId()] = ecs::component::Size{3, 3};

        ecs::systems::GunFireSystem gunSystem;
        _r.add_system(gunSystem);
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
        auto &size = _r.register_component<ecs::component::Size>();

        positions[player.getId()] = ecs::component::Position{100, 100};
        drawables[player.getId()] = ecs::component::Drawable{true};
        controllable[player.getId()] = ecs::component::Controllable{true, 0.9};
        sprite[player.getId()] = ecs::component::Sprite{PLAYER_SPRITE};
        animation[player.getId()] = ecs::component::Animations{sf::Clock(), 33, 20, 65, 0, 0, ecs::component::Object::Player};
        size[player.getId()] = ecs::component::Size{3, 3};

        ecs::systems::PlayerMouvementSystem playerMovementSystem;
        _r.add_system(playerMovementSystem);
    }

    void Context::setupBackground()
    {
        Entity firstBackground = _r.spawn_entity();
        _entitys.addEntity(firstBackground);
        Entity secondBackground = _r.spawn_entity();
        _entitys.addEntity(secondBackground);
        Entity thirdBackground = _r.spawn_entity();
        _entitys.addEntity(thirdBackground);
        Entity fourthBackground = _r.spawn_entity();
        _entitys.addEntity(fourthBackground);

        auto &positions = _r.register_component<ecs::component::Position>();
        auto &drawable = _r.register_component<ecs::component::Drawable>();
        auto &sprite = _r.register_component<ecs::component::Sprite>();
        auto &animation = _r.register_component<ecs::component::Animations>();
        auto &paralax = _r.register_component<ecs::component::Parallax>();
        auto &size = _r.register_component<ecs::component::Size>();

        paralax[firstBackground.getId()] = ecs::component::Parallax{true, 3, 1};
        paralax[secondBackground.getId()] = ecs::component::Parallax{true, 3, 1};
        paralax[thirdBackground.getId()] = ecs::component::Parallax{true, 1, 1};
        paralax[fourthBackground.getId()] = ecs::component::Parallax{true, 1, 1};

        sprite[firstBackground.getId()] = ecs::component::Sprite{BACKGROUND2_SPRITE};
        sprite[secondBackground.getId()] = ecs::component::Sprite{BACKGROUND2_SPRITE};
        sprite[thirdBackground.getId()] = ecs::component::Sprite{BACKGROUND4_SPRITE};
        sprite[fourthBackground.getId()] = ecs::component::Sprite{BACKGROUND4_SPRITE};

        drawable[firstBackground.getId()] = ecs::component::Drawable{true};
        drawable[secondBackground.getId()] = ecs::component::Drawable{true};
        drawable[thirdBackground.getId()] = ecs::component::Drawable{true};
        drawable[fourthBackground.getId()] = ecs::component::Drawable{true};

        positions[firstBackground.getId()] = ecs::component::Position{1920 * 0, 0};
        positions[secondBackground.getId()] = ecs::component::Position{1920 * 1, 0};
        positions[thirdBackground.getId()] = ecs::component::Position{1920 * 0, 0};
        positions[fourthBackground.getId()] = ecs::component::Position{1920 * 1, 0};

        animation[firstBackground.getId()] = ecs::component::Animations{sf::Clock(), 1920, 1080, 0, 0, 0, ecs::component::Object::Background};
        animation[secondBackground.getId()] = ecs::component::Animations{sf::Clock(), 1920, 1080, 0, 0, 0, ecs::component::Object::Background};
        animation[thirdBackground.getId()] = ecs::component::Animations{sf::Clock(), 1920, 1080, 0, 0, 0, ecs::component::Object::Background};
        animation[fourthBackground.getId()] = ecs::component::Animations{sf::Clock(), 1920, 1080, 0, 0, 0, ecs::component::Object::Background};

        size[firstBackground.getId()] = ecs::component::Size{7, 7};
        size[secondBackground.getId()] = ecs::component::Size{7, 7};
        size[thirdBackground.getId()] = ecs::component::Size{7, 7};
        size[fourthBackground.getId()] = ecs::component::Size{7, 7};

        ecs::systems::ParalaxSystem paralaxSystem;
        _r.add_system(paralaxSystem);
    }

    void Context::setup()
    {
        setupBackground();
        setupPlayer();
        setupWeapon();
    }

    int Context::run()
    {
        setup();
        auto &drawables = _r.get_components<ecs::component::Drawable>();
        auto &sprites = _r.get_components<ecs::component::Sprite>();
        auto &positions = _r.register_component<ecs::component::Position>();
        auto &animations = _r.register_component<ecs::component::Animations>();
        auto &size = _r.register_component<ecs::component::Size>();

        while (_window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
            }
            _window.clear();
            _r.run_systems();

            for (std::size_t i = 0; i < _entitys.size(); ++i) {
                if (drawables[i]->_drawable) {
                    sf::Texture texture;
                    if (sprites[i] && animations[i]) {
                        ImageResolver image(PATH_TO_ASSETS);
                        std::string pathToImage = image.getImage(sprites[i]->_pathToSprite);
                        texture.loadFromMemory(
                            pathToImage.c_str(),
                            pathToImage.size(),
                            sf::IntRect(
                                animations[i]->_x, animations[i]->_y, animations[i]->_width, animations[i]->_height
                            )
                        );
                    }
                    sf::Sprite sprite;
                    sprite.setPosition(positions[i]->_x, positions[i]->_y);
                    sprite.setScale(size[i]->_width, size[i]->_height);
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
