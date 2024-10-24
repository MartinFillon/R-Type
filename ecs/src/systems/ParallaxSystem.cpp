/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** ParallaxSystem
*/

#include "Systems/ParallaxSystem.hpp"
#include <memory>
#include "ComponentFactory.hpp"
#include "Components/Attributes.hpp"
#include "Components/Parallax.hpp"
#include "Components/Position.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::ParalaxSystem::
operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &)
{
    if (_clock.getMiliSeconds() < BACKGROUND_TICK) {
        return;
    }
    _clock.restart();
    auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();
    auto &parallax = r->register_if_not_exist<ecs::component::Parallax>();
    auto &positions = r->register_if_not_exist<ecs::component::Position>();
    auto &animation = r->register_if_not_exist<ecs::component::Animations>();

    for (auto &&[atr, pos, para, anim] : ecs::custom_zip(attributes, positions, parallax, animation)) {
        if (atr->_entity_type == ecs::component::Attributes::EntityType::Background &&
            anim->_clock.getSeconds() > (int)(1 / 60)) {
            if (pos->_x <= -SCREEN_WIDTH) {
                pos->_x = SCREEN_WIDTH * para->_multiplicator;
            }
            pos->_x -= para->_speed;
        }
    }
}
