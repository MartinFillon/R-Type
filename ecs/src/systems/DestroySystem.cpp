/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** DestroySystem
*/

#include "Systems/DestroySystem.hpp"

void ecs::systems::DestroySystem::operator()(Registry &r)
{
    if (_clock.getMiliSeconds() < DESTROY_TICK) {
        return;
    }
    _clock.restart();
    auto &destroyables = r.get_components<ecs::component::Destroyable>();
    auto &animations = r.get_components<ecs::component::Animations>();
    auto &sprites = r.get_components<ecs::component::Sprite>();
    int idx = 0;

    for (auto &&[anim, destroy, sprite] : ecs::custom_zip(animations, destroyables, sprites)) {
        if (!anim || !destroy || !sprite || !destroy->_destroyable) {
            idx += 1;
            continue;
        }

        if (sprite->_pathToSprite != DESTROY_SPRITE) {
            sprite->_pathToSprite = DESTROY_SPRITE;
            anim->_x = 0;
            anim->_y = 0;
            anim->_width = 65;
            anim->_height = 65;
            anim->_clock.restart();
            continue;
        }

        if (anim->_x > 315) {
            r.erase(idx);
        }

        if (anim->_clock.getSeconds() > DESTROY_ANIMATION) {
            anim->_x += anim->_width;
            anim->_clock.restart();
        }
        idx += 1;
    }
}
