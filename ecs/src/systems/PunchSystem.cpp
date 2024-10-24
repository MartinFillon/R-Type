/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PunchSystem
*/

#include "Systems/PunchSystem.hpp"
#include "Components/Animations.hpp"
#include "Components/KeyPressed.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::PunchSystem::operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
{
    auto &keys = r->get_components<ecs::component::KeyPressed>();
    auto &animations = r->get_components<ecs::component::Animations>();

    for (auto &&[key, anim] : custom_zip(keys, animations)) {
        if (!key || !anim) {
            continue;
        }

        if (key->_value != ecs::component::Key::Punch) {
            continue;
        }

        if (anim->_clock.getSeconds() < SPEED_PUNCH_ANIMATION) {
            continue;
        }
        anim->_clock.restart();

        if (anim->_x < END_OF_PUNCH_ANIMATION) {
            anim->_x += anim->_width + WIDTH_PADDING;
            anim->_width += WIDTH_PADDING;
        }
    }
}
