/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ThirdDMouvementSystem
*/

#include <iostream>
#include "Systems/ThirdDMouvementSystem.hpp"
#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Position3D.hpp"
#include "Components/Sprite.hpp"
#include "IContext.hpp"
#include "Systems/ISystems.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

namespace ecs::systems {
    ThirdDMouvementSystem::ThirdDMouvementSystem(const nlohmann::json &config) {}

    void ThirdDMouvementSystem::operator()(
        std::shared_ptr<Registry> &r,
        std::shared_ptr<IContext> ctx,
        ComponentFactory &factory
    )
    {
        auto &positions = r->get_components<ecs::component::Position3D>();
        auto &keys = r->get_components<ecs::component::KeyPressed>();
        auto &controllables = r->get_components<ecs::component::Controllable>();

        for (auto &&[pos, key, ctrl] :
            custom_zip(positions, keys, controllables)) {

            if (!ctrl->_controllable) {
                continue;
            }

            if (key->_value == ecs::component::Key::Left) {
                pos->_x += ctrl->_speed;
            }

            if (key->_value == ecs::component::Key::Right) {
                pos->_x -= ctrl->_speed;
            }

            if (key->_value == ecs::component::Key::Up) {
                pos->_z += ctrl->_speed;
            }

            if (key->_value == ecs::component::Key::Down) {
                pos->_z -= ctrl->_speed;
            }

        }
    }

} // namespace ecs::systems
