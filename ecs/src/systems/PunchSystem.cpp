/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PunchSystem
*/

#include <iostream>

#include "Systems/PunchSystem.hpp"
#include "Components/Animations.hpp"
#include "Components/KeyPressed.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::PunchSystem::operator()(Registry &r, std::shared_ptr<IContext> ctx)
{
    auto &keys = r.get_components<ecs::component::KeyPressed>();
    auto &animations = r.get_components<ecs::component::Animations>();

    for (auto &&[key, anim] : custom_zip(keys, animations)) {
        if (!key || !anim) {
            continue;
        }

        if (key->_value != ecs::component::Key::Punch) {
            continue;
        }

        if (anim->_clock.getSeconds() < 0.09) {
            continue;
        }
        anim->_clock.restart();
        std::cerr << "anim x: " << anim->_x << "\n";
        if (anim->_x < 130) {
            anim->_x += anim->_width + 5;
            anim->_width += 5;
        }
    }
}
