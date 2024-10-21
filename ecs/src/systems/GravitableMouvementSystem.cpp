/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GravitableMouvementSystem
*/

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

        if (key->_value == ecs::component::Key::Up && !gravit->_isJumping && !gravit->_isFalling && pos->_y == initialY) {
            gravit->_isJumping = true;
        }

        if (gravit->_isJumping && pos->_y > targetY && anim->_clock.getSeconds() > 0.2) {
            pos->_y -= gravit->_gravityFall;
            anim->_x += anim->_width;
            anim->_clock.restart();
        }

        if (gravit->_isJumping && pos->_y <= targetY) {
            gravit->_isJumping = false;
            gravit->_isFalling = true;
        }

        if (gravit->_isFalling && pos->_y < initialY && anim->_clock.getSeconds() > 0.2) {
            pos->_y += gravit->_gravityFall + (gravit->_gravityFall - 1);
            anim->_x -= anim->_width;
            anim->_clock.restart();
        }

        if (anim->_x > 1000) {
            anim->_x = 0;
            anim->_y = 0;
            anim->_width = 100;
            anim->_height = 110;
        }

        if (gravit->_isFalling && pos->_y >= initialY) {
            pos->_y = initialY;
            gravit->_isFalling = false;
            key->_value = ecs::component::Key::NoneKey;
        }
    }
}
