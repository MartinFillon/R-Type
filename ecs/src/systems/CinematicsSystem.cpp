/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CinematicsSystem
*/

#include "Systems/CinematicsSystem.hpp"
#include "Components/Animations.hpp"
#include "Components/Cinematic.hpp"
#include "Components/Position.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::CinematicsSystem::operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
{
    auto &cinematics = r->get_components<ecs::component::Cinematic>();
    auto &animations = r->get_components<ecs::component::Animations>();
    auto &animPositions = r->get_components<ecs::component::Position>();

    for (auto &&[cine]: custom_zip(cinematics)) {
        if (!cine) {
            continue;
        }

        if (cine->_state != true) {
            continue;
        }

        for (auto &&[anim, animPos]: custom_zip(animations, animPositions)) {
            if (!anim || !animPos) {
                continue;
            }

            if (anim->_object != cine->_anim._object &&
                anim->_type != cine->_anim._type) {
                continue;
            }

            if (animPos->_x < cine->_end._x) {
                animPos->_x += cine->_speed;
            } else if (animPos->_x > cine->_end._x) {
                animPos->_x -= cine->_speed;
            }

            if (animPos->_y < cine->_end._y) {
                animPos->_y += cine->_speed;
            } else if (animPos->_y > cine->_end._y) {
                animPos->_y -= cine->_speed;
            }

            if (animPos->_x == cine->_end._x && animPos->_y == cine->_end._y) {
                cine->_state = false;
            }
        }
    }
}
