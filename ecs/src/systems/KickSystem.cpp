/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** KickSystem
*/

#include "Systems/KickSystem.hpp"
#include "Components/Animations.hpp"
#include "Components/KeyPressed.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::KickSystem::operator()(Registry &r, std::shared_ptr<IContext> ctx)
{
    auto &keys = r.get_components<ecs::component::KeyPressed>();
    auto &animations = r.get_components<ecs::component::Animations>();

    for (auto &&[key, anim] : custom_zip(keys, animations)) {
        if (!key || !anim) {
            continue;
        }

        if (key->_value != ecs::component::Key::Kick) {
            continue;
        }

        if (anim->_clock.getSeconds() < 0.09) {
            continue;
        }
        anim->_clock.restart();

        if (anim->_x < 280) {
            anim->_x += anim->_width + 5;
            anim->_width += 2;
        }
    }
}