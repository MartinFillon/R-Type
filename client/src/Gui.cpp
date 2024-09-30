/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#include "Gui.hpp"

#include "Components/Parallax.hpp"

#include "ImageResolver.hpp"
#include "Systems/GunFireSystem.hpp"
#include "Systems/ParallaxSystem.hpp"
#include "Systems/PlayerMouvementSystem.hpp"
#include "Systems/basicRandomEnnemiesSystem.hpp"

namespace rtype {
    Gui::Gui() : ecs::Context()
    {
        setupBackground();
        setupPlayer();
        setupWeapon();
        setupBasicEnnemies();
    }

    Gui::~Gui() {}

    void Gui::setupWeapon()
    {
        ecs::systems::GunFireSystem gunSystem;
        _r.add_system(gunSystem);
    }

    void Gui::setupBasicEnnemies()
    {
        ecs::systems::BasicRandomEnnemiesSystem basicEnnemies;
        _r.add_system(basicEnnemies);
    }

    void Gui::setupPlayer()
    {
        ecs::Entity player = _r.spawn_entity();
        _r._entitys.addEntity(player);

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
        animation[player.getId()] =
            ecs::component::Animations{sf::Clock(), 33, 20, 65, 0, 0, ecs::component::Object::Player};
        size[player.getId()] = ecs::component::Size{3, 3};

        ecs::systems::PlayerMouvementSystem playerMovementSystem;
        _r.add_system(playerMovementSystem);
    }

    void Gui::setupBackground()
    {
        ecs::Entity firstBackground = _r.spawn_entity();
        _r._entitys.addEntity(firstBackground);
        ecs::Entity secondBackground = _r.spawn_entity();
        _r._entitys.addEntity(secondBackground);
        ecs::Entity thirdBackground = _r.spawn_entity();
        _r._entitys.addEntity(thirdBackground);
        ecs::Entity fourthBackground = _r.spawn_entity();
        _r._entitys.addEntity(fourthBackground);

        auto &positions = _r.register_component<ecs::component::Position>();
        auto &drawable = _r.register_component<ecs::component::Drawable>();
        auto &sprite = _r.register_component<ecs::component::Sprite>();
        auto &animation = _r.register_component<ecs::component::Animations>();
        auto &parallax = _r.register_component<ecs::component::Parallax>();
        auto &size = _r.register_component<ecs::component::Size>();

        parallax[firstBackground.getId()] = ecs::component::Parallax{true, 3, 1};
        parallax[secondBackground.getId()] = ecs::component::Parallax{true, 3, 1};
        parallax[thirdBackground.getId()] = ecs::component::Parallax{true, 1, 1};
        parallax[fourthBackground.getId()] = ecs::component::Parallax{true, 1, 1};

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

        animation[firstBackground.getId()] =
            ecs::component::Animations{sf::Clock(), 1920, 1080, 0, 0, 0, ecs::component::Object::Background};
        animation[secondBackground.getId()] =
            ecs::component::Animations{sf::Clock(), 1920, 1080, 0, 0, 0, ecs::component::Object::Background};
        animation[thirdBackground.getId()] =
            ecs::component::Animations{sf::Clock(), 1920, 1080, 0, 0, 0, ecs::component::Object::Background};
        animation[fourthBackground.getId()] =
            ecs::component::Animations{sf::Clock(), 1920, 1080, 0, 0, 0, ecs::component::Object::Background};

        size[firstBackground.getId()] = ecs::component::Size{7, 7};
        size[secondBackground.getId()] = ecs::component::Size{7, 7};
        size[thirdBackground.getId()] = ecs::component::Size{7, 7};
        size[fourthBackground.getId()] = ecs::component::Size{7, 7};

        ecs::systems::ParalaxSystem parallaxSystem;
        _r.add_system(parallaxSystem);
    }

    int Gui::run()
    {
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

            for (std::size_t i = 0; i < _r._entitys.size(); ++i) {
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
