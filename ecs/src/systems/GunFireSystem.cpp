/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GunFireSystem
*/

#include "Systems/GunFireSystem.hpp"
#include <memory>
#include "ComponentFactory.hpp"
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

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
        auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();
        auto &positions = r->register_if_not_exist<ecs::component::Position>();
        auto &controllables = r->register_if_not_exist<ecs::component::Controllable>();
        auto &animations = r->register_if_not_exist<ecs::component::Animations>();
        auto &drawables = r->register_if_not_exist<ecs::component::Drawable>();
        auto &destroyables = r->register_if_not_exist<ecs::component::Destroyable>();
        ecs::component::Position playerPos = {0, 0};

        for (std::size_t i = 0; i < positions.size(); ++i) {
            if (attributes[i] && attributes[i]->_entity_type == ecs::component::Attributes::EntityType::Player) {
                playerPos._x = positions[i]->_x + 100;
                playerPos._y = positions[i]->_y + 10;
                break;
            }
        }

        if (playerPos._x == 0.0 && playerPos._y == 0.0) {
            return;
        }

        for (auto &&[atr, pos, contr, anim, draw, destroyable] :
             custom_zip(attributes, positions, controllables, animations, drawables, destroyables)) {
            if (draw && !draw->_drawable) {
                continue;
            }
            if (pos && contr && anim && atr->_entity_type == ecs::component::Attributes::EntityType::Weapon &&
                atr->_secondary_type == ecs::component::Attributes::SecondaryType::None && destroyable &&
                destroyable->_state == ecs::component::Destroyable::DestroyState::ALIVE) {
                if (anim->_x < 30) {
                    pos = playerPos;
                }
                if (anim->_clock.getSeconds() > PROJECTILE_SPEED_ANIMATION && anim->_x < 30) {
                    anim->_x += anim->_width;
                    anim->_clock.restart();
                }
                if (anim->_x > 30 && draw->_drawable) {
                    pos->_x += contr->_speed;
                }
                draw->_drawable = true;
            }
        }
    }
} // namespace ecs
