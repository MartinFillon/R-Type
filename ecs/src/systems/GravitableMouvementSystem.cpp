/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GravitableMouvementSystem
*/

#include <iostream>

#include "Systems/GravitableMouvementSystem.hpp"
#include "Components/Animations.hpp"
#include "Components/Gravitable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Position.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::GravitableMouvementSystem::operator()(Registry &r, std::shared_ptr<IContext> ctx)
{
    auto &positions = r.get_components<ecs::component::Position>();
    auto &animations = r.get_components<ecs::component::Animations>();
    auto &gravitables = r.get_components<ecs::component::Gravitable>();
    auto &keys = r.get_components<ecs::component::KeyPressed>();
    int initialY = INITIAL_Y;
    int targetY = MAX_Y;

    for (auto &&[pos, anim, gravit, key] : custom_zip(positions, animations, gravitables, keys)) {
        if (!pos || !anim || !gravit || !key) {
            continue;
        }
        if (anim->_clock.getSeconds() < 0.1) {
            continue;
        }

        if (key->_value == ecs::component::Key::Up && !gravit->_isJumping && !gravit->_isFalling && pos->_y == initialY) {
            gravit->_isJumping = true;
        }

        anim->_clock.restart();
        if (gravit->_isJumping && pos->_y > targetY) {
            pos->_y -= (gravit->_gravityFall + GRAVITY_JUMP_PADDING);
            if (anim->_x < END_SPRITE_SHEET) {
                anim->_x += anim->_width + 5;
            }
        }

        if (gravit->_isJumping && pos->_y <= targetY) {
            gravit->_isJumping = false;
            gravit->_isFalling = true;
        }

        if (gravit->_isFalling && (pos->_y + anim->_height) <= initialY) {
            pos->_y += ((gravit->_gravityFall + 20) GRAVITY_DOWN_PADDING);
            if (anim->_x < END_SPRITE_SHEET) {
                anim->_x += anim->_width + 5;
            }
        }

        if (gravit->_isFalling && (pos->_y + anim->_height) >= initialY) {
            pos->_y = INITIAL_Y;
            pos->_y = initialY;
            gravit->_isFalling = false;
            key->_value = ecs::component::Key::NoneKey;
        }
    }
}
