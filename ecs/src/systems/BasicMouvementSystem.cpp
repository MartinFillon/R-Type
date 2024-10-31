/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BasicMouvementSystem
*/

#include "Systems/BasicMouvementSystem.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Gravitable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Position.hpp"
#include "Registry.hpp"
#include "SystemsManager.hpp"
#include "ZipperIterator.hpp"

namespace ecs::systems {
    void BasicMouvementSystem::operator()(
        std::shared_ptr<Registry> &r,
        std::shared_ptr<IContext> ctx,
        ComponentFactory &factory
    )
    {
        auto &positions = r->get_components<ecs::component::Position>();
        auto &animations = r->get_components<ecs::component::Animations>();
        auto &gravitables = r->get_components<ecs::component::Gravitable>();
        auto &keys = r->get_components<ecs::component::KeyPressed>();
        auto &controllables = r->get_components<ecs::component::Controllable>();
        auto &destroyables = r->get_components<ecs::component::Destroyable>();

        for (auto &&[pos, anim, grav, key, ctrl, destroyable] :
             custom_zip(positions, animations, gravitables, keys, controllables, destroyables)) {
            if (!pos || !anim || !grav || !key || !ctrl || !destroyable ||
                destroyable->_state != ecs::component::Destroyable::DestroyState::ALIVE) {
                continue;
            }

            if (!ctrl->_controllable) {
                continue;
            }

            if (key->_value == ecs::component::Key::Left) {
                pos->_x -= ctrl->_speed;
            }

            if (key->_value == ecs::component::Key::Right) {
                pos->_x += ctrl->_speed;
            }
        }
    }

} // namespace ecs::systems
