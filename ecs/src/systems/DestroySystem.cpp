/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** DestroySystem
*/

#include "Systems/DestroySystem.hpp"
#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include "ComponentFactory.hpp"
#include "Components/Attributes.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Sprite.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::DestroySystem::operator()(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<IContext> ctx,
    ComponentFactory &factory
)
{
    if (_clock.getMiliSeconds() < DESTROY_TICK) {
        return;
    }

    _clock.restart();

    auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();
    auto &destroyables = r->register_if_not_exist<ecs::component::Destroyable>();
    auto &animations = r->register_if_not_exist<ecs::component::Animations>();
    auto &sprites = r->register_if_not_exist<ecs::component::Sprite>();

    for (auto &&[attribute, destroyable, animation, sprite] :
         ecs::custom_zip(attributes, destroyables, animations, sprites)) {
        if (!destroyable || destroyable->_state == ecs::component::Destroyable::DestroyState::ALIVE) {
            continue;
        }

        destroyable->_state = ecs::component::Destroyable::DestroyState::DESTROYING;

        if (!destroyable->_animate) {
            destroyable->_state = ecs::component::Destroyable::DestroyState::DESTROYED;

            r->erase(attribute->_identifyer);

            if (ctx) {
                ctx->destroyObject(attribute->_identifyer);
            }

            continue;
        }

        if (destroyable->_animate) {
            if (!animation || !sprite) {
                destroyable->_state = ecs::component::Destroyable::DestroyState::DESTROYED;

                r->erase(attribute->_identifyer);

                if (ctx) {
                    ctx->destroyObject(attribute->_identifyer);
                }

                continue;
            }

            if (sprite->_pathToSprite != DESTROY_SPRITE) {
                sprite->_pathToSprite = DESTROY_SPRITE;
                animation->_x = 0;
                animation->_y = 0;
                animation->_width = 65;
                animation->_height = 65;
                continue;
            }

            if (animation->_x > 315) {
                destroyable->_state = ecs::component::Destroyable::DestroyState::DESTROYED;

                r->erase(attribute->_identifyer);

                if (ctx) {
                    ctx->destroyObject(attribute->_identifyer);
                }

                continue;
            }

            if (animation->_clock.getSeconds() > DESTROY_ANIMATION) {
                animation->_x += animation->_width;
                animation->_clock.restart();
            }
        }
    }
}
