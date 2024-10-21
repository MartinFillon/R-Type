/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SitDownSystem
*/

#include "Systems/SitDownSystem.hpp"
#include <memory>
#include "Components/Animations.hpp"
#include "Components/KeyPressed.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::SitDownSystem::operator()(Registry &r, std::shared_ptr<IContext> ctx)
{
    auto &keys = r.get_components<ecs::component::KeyPressed>();
    auto &animations = r.get_components<ecs::component::Animations>();

    for (auto &&[key, anim] : custom_zip(keys, animations)) {
        if (!anim || !key) {
            continue;
        }

        if (key->_value != ecs::component::Key::Down) {
            continue;
        }

        if (anim->_x >= 550) {
            break;
        }

        if (anim->_clock.getSeconds() > 0.2) {
            anim->_x += anim->_width;
            anim->_clock.restart();
        }

    }
}
