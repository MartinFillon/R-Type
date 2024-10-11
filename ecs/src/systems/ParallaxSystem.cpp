/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** ParallaxSystem
*/

#include "Systems/ParallaxSystem.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::ParalaxSystem::operator()(Registry &r, std::shared_ptr<IContext> ctx)
{
    if (_clock.getMiliSeconds() < BACKGROUND_TICK) {
        return;
    }
    _clock.restart();
    auto &paralax = r.get_components<ecs::component::Parallax>();
    auto &positions = r.get_components<ecs::component::Position>();
    auto &animation = r.get_components<ecs::component::Animations>();

    for (auto &&[pos, para, anim] : ecs::custom_zip(positions, paralax, animation)) {
        if (anim->_object == ecs::component::Object::Background && anim->_clock.getSeconds() > (int)(1 / 60)) {
            if (pos->_x <= -SCREEN_WIDTH) {
                pos->_x = SCREEN_WIDTH * para->_multiplicator;
            }
            pos->_x -= para->_speed;
        }
    }
}
