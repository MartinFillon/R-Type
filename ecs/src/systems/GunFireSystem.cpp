/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GunFireSystem
*/

#include "Systems/GunFireSystem.hpp"
#include <memory>
#include "ComponentFactory.hpp"
#include "Registry.hpp"

namespace ecs {

    void systems::GunFireSystem::operator()(
        std::shared_ptr<Registry> &r,
        std::shared_ptr<IContext> ctx,
        ComponentFactory &factory
    )
    {
        if (_clock.getMiliSeconds() < PROJECTIL_TICK) {
            return;
        }
        _clock.restart();
        auto &positions = r->get_components<ecs::component::Position>();
        auto &controllable = r->get_components<ecs::component::Controllable>();
        auto &animations = r->get_components<ecs::component::Animations>();
        auto &drawable = r->get_components<ecs::component::Drawable>();
        auto &destroyable = r->get_components<ecs::component::Destroyable>();
        ecs::component::Position playerPos = {0, 0};

        for (std::size_t i = 0; i < positions.size(); ++i) {
            if (animations[i] && animations[i]->_object == ecs::component::Object::Player) {
                playerPos._x = positions[i]->_x + 100;
                playerPos._y = positions[i]->_y + 10;
                break;
            }
        }

        if (playerPos._x == 0.0 && playerPos._y == 0.0) {
            return;
        }

        for (std::size_t i = 0; i < positions.size(); ++i) {
            if (drawable[i] && !drawable[i]->_drawable) {
                continue;
            }
            if (positions[i] && controllable[i] && animations[i] &&
                animations[i]->_object == ecs::component::Object::Weapon &&
                animations[i]->_type == ecs::component::Type::None) {
                if (animations[i]->_x < 30) {
                    positions[i] = playerPos;
                }
                if (animations[i]->_clock.getSeconds() > PROJECTILE_SPEED_ANIMATION && animations[i]->_x < 30) {
                    animations[i]->_x += animations[i]->_width;
                    animations[i]->_clock.restart();
                }
                if (animations[i]->_x > 30 && drawable[i]->_drawable) {
                    positions[i]->_x += controllable[i]->_speed;
                }
                drawable[i]->_drawable = true;
            }
        }
    }
} // namespace ecs
