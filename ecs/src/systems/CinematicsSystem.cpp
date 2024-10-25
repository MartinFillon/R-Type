/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CinematicsSystem
*/

#include "Systems/CinematicsSystem.hpp"
#include "Components/Attributes.hpp"
#include "Components/Cinematic.hpp"
#include "Components/Position.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::CinematicsSystem::operator()(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<IContext> ctx,
    ComponentFactory &factory
)
{
    auto &attributes = r->get_components<ecs::component::Attributes>();
    auto &cinematics = r->get_components<ecs::component::Cinematic>();
    auto &animPositions = r->get_components<ecs::component::Position>();

    for (auto &&[cine] : custom_zip(cinematics)) {
        if (!cine) {
            continue;
        }

        if (cine->_state != true) {
            continue;
        }

        for (auto &&[atr, animPos] : custom_zip(attributes, animPositions)) {
            if (!atr || !animPos) {
                continue;
            }

            if (atr->_entity_type != cine->_atr._entity_type && atr->_secondary_type != cine->_atr._secondary_type) {
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
