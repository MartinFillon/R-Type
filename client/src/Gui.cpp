/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#include "Gui.hpp"
#include <iostream>

#include "ImageResolver.hpp"
#include "Systems/GunFireSystem.hpp"
#include "Systems/ParallaxSystem.hpp"
#include "Systems/PlayerMouvementSystem.hpp"
#include "Systems/BasicRandomEnnemiesSystem.hpp"

namespace rtype {
    Gui::Gui() : ecs::Context()
    {
        _factory = ecs::ComponentFactory(_r);
        setupBackground();
        setupPlayer();
        setupWeapon();
        setupBasicEnnemies();
    }

    Gui::~Gui() {}

    void Gui::setupWeapon()
    {
        ecs::systems::GunFireSystem gunSystem;
        _r->add_system(gunSystem);
    }

    void Gui::setupBasicEnnemies()
    {
        ecs::systems::BasicRandomEnnemiesSystem basicEnnemies;
        _r->add_system(basicEnnemies);
    }

    void Gui::setupPlayer()
    {
        _factory.createEntity("config/player.json");

        std::cout << "Player created" << std::endl;

        ecs::systems::PlayerMouvementSystem playerMovementSystem;
        _r->add_system(playerMovementSystem);
    }

    void Gui::setupBackground()
    {
        _factory.createEntity("config/background/background.json");
        _factory.createEntity("config/background/background_2.json");
        _factory.createEntity("config/background/background_3.json");
        _factory.createEntity("config/background/background_4.json");

        ecs::systems::ParalaxSystem parallaxSystem;
        _r->add_system(parallaxSystem);
    }

    int Gui::run()
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

            for (std::size_t i = 0; i < _r->_entitys.size(); ++i) {
                if (drawables[i]->_drawable) {
                    sf::Texture texture;
                    if (sprites[i] && animations[i]) {
                        ecs::ImageResolver image(PATH_TO_ASSETS);
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

} // namespace rtype
