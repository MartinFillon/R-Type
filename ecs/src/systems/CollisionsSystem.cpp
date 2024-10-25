/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** Collision system file
*/

#include "Systems/CollisionsSystem.hpp"
#include <memory>
#include <spdlog/spdlog.h>
#include "ComponentFactory.hpp"
#include "Components/Attributes.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Invincibility.hpp"
#include "Components/Life.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

namespace ecs {
    namespace systems {
        void CollisionsSystem::operator()(
            std::shared_ptr<Registry> &r,
            std::shared_ptr<IContext> ctx,
            ComponentFactory &factory
        )
        {
            auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();
            auto &positions = r->register_if_not_exist<ecs::component::Position>();
            auto &drawables = r->register_if_not_exist<ecs::component::Drawable>();
            auto &animations = r->register_if_not_exist<ecs::component::Animations>();
            auto &destroyables = r->register_if_not_exist<ecs::component::Destroyable>();
            auto &lifes = r->register_if_not_exist<ecs::component::Life>();
            auto &sizes = r->register_if_not_exist<ecs::component::Size>();
            auto &invincibilities = r->register_if_not_exist<ecs::component::Invincibility>();

            for (auto
                     &&[attribute_i,
                        position_i,
                        drawable_i,
                        animation_i,
                        destroyable_i,
                        life_i,
                        size_i,
                        invincibility_i] :
                 ecs::custom_zip(
                     attributes, positions, drawables, animations, destroyables, lifes, sizes, invincibilities
                 )) {
                if (!attribute_i || !position_i || !animation_i || !size_i || !destroyable_i || !life_i ||
                    (drawable_i && !drawable_i->_drawable)) {
                    spdlog::debug(
                        "{}, {}, {}, {}, {}, {}, {}, {}, {}",
                        attribute_i.has_value(),
                        position_i.has_value(),
                        animation_i.has_value(),
                        size_i.has_value(),
                        destroyable_i.has_value(),
                        life_i.has_value(),
                        drawable_i.has_value(),
                        drawable_i->_drawable
                    );
                    continue;
                }

                spdlog::info(
                    "{}, {}, {}, {}, {}, {}, {}, {}, {}",
                    attribute_i.has_value(),
                    position_i.has_value(),
                    animation_i.has_value(),
                    size_i.has_value(),
                    destroyable_i.has_value(),
                    life_i.has_value(),
                    drawable_i.has_value(),
                    drawable_i->_drawable
                );

                if (attribute_i->_entity_type == ecs::component::Attributes::EntityType::Background ||
                    destroyable_i->_state != ecs::component::Destroyable::DestroyState::ALIVE) {
                    continue;
                }

                double i_width = animation_i->_width * (size_i ? size_i->_width : 1.0);
                double i_height = animation_i->_height * (size_i ? size_i->_height : 1.0);

                if ((position_i->_x > WIDTH_MAX_LIMIT || position_i->_x < WIDTH_MIN_LIMIT) ||
                    (position_i->_y > HEIGHT_MAX_LIMIT || position_i->_y < HEIGHT_MIN_LIMIT)) {
                    destroyable_i->_state = ecs::component::Destroyable::DestroyState::WAITING;
                    continue;
                }

                for (auto
                         &&[attribute_j,
                            position_j,
                            drawable_j,
                            animation_j,
                            destroyable_j,
                            life_j,
                            size_j,
                            invincibility_j] :
                     ecs::custom_zip(
                         attributes, positions, drawables, animations, destroyables, lifes, sizes, invincibilities
                     )) {
                    if (!attribute_j || !position_j || !animation_j || !size_j || !destroyable_j || !life_j ||
                        (drawable_j && !drawable_j->_drawable)) {
                        continue;
                    }

                    if (attribute_j->_entity_type == ecs::component::Attributes::EntityType::Background ||
                        destroyable_j->_state != ecs::component::Destroyable::DestroyState::ALIVE) {
                        continue;
                    }

                    if (attribute_i->_identifyer == attribute_j->_identifyer) {
                        continue;
                    }

                    double j_width = animation_j->_width * (size_j ? size_j->_width : 1.0);
                    double j_height = animation_j->_height * (size_j ? size_j->_height : 1.0);

                    if ((position_j->_x > WIDTH_MAX_LIMIT || position_j->_x < WIDTH_MIN_LIMIT) ||
                        (position_j->_y > HEIGHT_MAX_LIMIT || position_j->_y < HEIGHT_MIN_LIMIT)) {
                        destroyable_j->_state = ecs::component::Destroyable::DestroyState::WAITING;
                        continue;
                    }

                    if (attribute_i->_secondary_type == ecs::component::Attributes::SecondaryType::Milespates &&
                        attribute_j->_secondary_type == ecs::component::Attributes::SecondaryType::Milespates) {
                        continue;
                    }

                    if ((attribute_i->_entity_type == ecs::component::Attributes::EntityType::Weapon &&
                         attribute_i->_secondary_type == ecs::component::Attributes::SecondaryType::None &&
                         attribute_j->_entity_type == ecs::component::Attributes::EntityType::Player) ||
                        (attribute_j->_entity_type == ecs::component::Attributes::EntityType::Weapon &&
                         attribute_j->_secondary_type == ecs::component::Attributes::SecondaryType::None &&
                         attribute_i->_entity_type == ecs::component::Attributes::EntityType::Player)) {
                        continue;
                    }

                    if ((attribute_i->_entity_type == ecs::component::Attributes::EntityType::Weapon &&
                         attribute_i->_secondary_type == ecs::component::Attributes::SecondaryType::Basic &&
                         attribute_j->_entity_type == ecs::component::Attributes::EntityType::Ennemy) ||
                        (attribute_j->_entity_type == ecs::component::Attributes::EntityType::Weapon &&
                         attribute_j->_secondary_type == ecs::component::Attributes::SecondaryType::Basic &&
                         attribute_i->_entity_type == ecs::component::Attributes::EntityType::Ennemy)) {
                        continue;
                    }

                    if (((position_i->_x + i_width >= position_j->_x && position_i->_x <= position_j->_x + j_width) &&
                         (position_i->_y + i_height >= position_j->_y && position_i->_y <= position_j->_y + j_height)
                        ) &&
                        attribute_i->_entity_type != attribute_j->_entity_type) {

                        if (!invincibility_i.has_value()) {
                            life_i->_life = life_i->_life - 1;
                        }
                        if (!invincibility_j.has_value()) {
                            life_j->_life = life_j->_life - 1;
                        }

                        if (invincibility_i.has_value() && !invincibility_i->_invincible) {
                            life_i->_life = life_i->_life - 1;
                            invincibility_i->_invincible = true;
                            invincibility_i->_clock.restart();
                        }
                        if (invincibility_j.has_value() && !invincibility_j->_invincible) {
                            life_j->_life = life_j->_life - 1;
                            invincibility_j->_invincible = true;
                            invincibility_j->_clock.restart();
                        }

                        if (life_i->_life <= 0) {
                            destroyable_i->_state = ecs::component::Destroyable::DestroyState::WAITING;
                        }
                        if (life_j->_life <= 0) {
                            destroyable_j->_state = ecs::component::Destroyable::DestroyState::WAITING;
                        }

                        continue;
                    }
                }
            }
        }
    } // namespace systems
} // namespace ecs
