/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** RegistryWrapper
*/

#include "RegistryWrapper.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include "Registry.hpp"
#include "TextureManager.hpp"
#include "ZipperIterator.hpp"

namespace rtype::client {
    RegistryWrapper::RegistryWrapper()
        : _client(std::make_shared<ecs::Registry>()), _server(std::make_shared<ecs::Registry>())
    {
        _server->register_component<ecs::component::Size>();
        _server->register_component<ecs::component::Sprite>();
        _server->register_component<ecs::component::Drawable>();
        _server->register_component<ecs::component::Position>();
        _server->register_component<ecs::component::Animations>();

        _client->register_component<ecs::component::Size>();
        _client->register_component<ecs::component::Sprite>();
        _client->register_component<ecs::component::Drawable>();
        _client->register_component<ecs::component::Position>();
        _client->register_component<ecs::component::Animations>();
    }

    RegistryWrapper::~RegistryWrapper() {}

    static void drawRegistry(
        sf::RenderWindow &window,
        TextureManager &textureManager,
        std::shared_ptr<ecs::Registry> &registry
    )
    {
        auto &sizes = registry->get_components<ecs::component::Size>();
        auto &sprites = registry->get_components<ecs::component::Sprite>();
        auto &drawables = registry->get_components<ecs::component::Drawable>();
        auto &positions = registry->get_components<ecs::component::Position>();
        auto &animations = registry->get_components<ecs::component::Animations>();

        for (auto &&[draw, anim, spri, si, pos] : ecs::custom_zip(drawables, animations, sprites, sizes, positions)) {

            if (!draw || !anim || !spri || !si || !pos) {
                continue;
            }

            if (spri->_pathToSprite.empty()) {
                continue;
            }

            sf::Sprite sprite;

            sprite.setPosition(pos->_x, pos->_y);
            sprite.setScale(si->_width, si->_height);
            sprite.setTexture(textureManager.getTexture(spri->_pathToSprite));
            sprite.setTextureRect(sf::IntRect(anim->_x, anim->_y, anim->_width, anim->_height));

            window.draw(sprite);
        }
    }

    void RegistryWrapper::draw(sf::RenderWindow &window, TextureManager &textureManager)
    {
        drawRegistry(window, textureManager, _client);
        drawRegistry(window, textureManager, _server);
    }

    void RegistryWrapper::run_systems(std::shared_ptr<ecs::IContext> ctx)
    {
        _client->run_systems(ctx);
        _server->run_systems(ctx);
    }

} // namespace rtype::client
