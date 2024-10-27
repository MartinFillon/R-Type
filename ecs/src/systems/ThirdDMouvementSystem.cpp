/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ThirdDMouvementSystem
*/

#include "Systems/ThirdDMouvementSystem.hpp"
#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Gravitable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Position3D.hpp"
#include "IContext.hpp"
#include "Systems/ISystems.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"
#include <unordered_map>

namespace ecs::systems {
    ThirdDMouvementSystem::ThirdDMouvementSystem(const nlohmann::json &config) {}

    void ThirdDMouvementSystem::operator()(
        std::shared_ptr<Registry> &r,
        std::shared_ptr<IContext> ctx,
        ComponentFactory &factory
    )
    {
        auto &positions = r->get_components<ecs::component::Position3D>();
        auto &animations = r->get_components<ecs::component::Animations>();
        auto &keys = r->get_components<ecs::component::KeyPressed>();
        auto &controllables = r->get_components<ecs::component::Controllable>();
        auto &destroyables = r->get_components<ecs::component::Destroyable>();

        for (auto &&[pos, anim, key, ctrl, destroyable] :
             custom_zip(positions, animations, keys, controllables, destroyables)) {
            if (!pos || !anim || !key || !ctrl || !destroyable ||
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

            if (key->_value == ecs::component::Key::Up) {
                pos->_z -= ctrl->_speed;
            }

            if (key->_value == ecs::component::Key::Down) {
                pos->_z += ctrl->_speed;
            }

        }
    }

} // namespace ecs::systems
