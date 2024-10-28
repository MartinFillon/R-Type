/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** DestroySystem
*/

#include "Systems/DestroySystem.hpp"
#include <iostream>
#include <memory>
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

    for (size_t i = 0; i < destroyables.size(); i++) {
        if (!destroyables[i] || destroyables[i]->_state == ecs::component::Destroyable::DestroyState::ALIVE) {
            continue;
        }

        destroyables[i]->_state = ecs::component::Destroyable::DestroyState::DESTROYING;

        if (!destroyables[i]->_animate) {
            destroyables[i]->_state = ecs::component::Destroyable::DestroyState::DESTROYED;
            r->erase(i);

            if (ctx) {
                ctx->destroyObject(i);
            }

            continue;
        }

        if (destroyables[i]->_animate) {
            if (!animations[i] || !sprites[i]) {
                destroyables[i]->_state = ecs::component::Destroyable::DestroyState::DESTROYED;
                r->erase(i);

                if (ctx) {
                    ctx->destroyObject(i);
                }

                continue;
            }

            if (sprites[i]->_pathToSprite != DESTROY_SPRITE) {
                sprites[i]->_pathToSprite = DESTROY_SPRITE;
                animations[i]->_x = 0;
                animations[i]->_y = 0;
                animations[i]->_width = 65;
                animations[i]->_height = 65;
                continue;
            }

            if (animations[i]->_x > 315) {
                destroyables[i]->_state = ecs::component::Destroyable::DestroyState::DESTROYED;
                r->erase(i);

                if (ctx) {
                    ctx->destroyObject(i);
                }

                continue;
            }

            if (animations[i]->_clock.getSeconds() > DESTROY_ANIMATION) {
                animations[i]->_x += animations[i]->_width;
                animations[i]->_clock.restart();
            }
        }
    }
}
