/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** Collision system file
*/

#include "Systems/CollisionsSystem.hpp"
#include <memory>
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
            auto &attribut = r->register_if_not_exist<component::Attributes>();
            auto &position = r->register_if_not_exist<component::Position>();
            auto &drawable = r->register_if_not_exist<component::Drawable>();
            auto &animation = r->register_if_not_exist<component::Animations>();
            auto &destroyable = r->register_if_not_exist<component::Destroyable>();
            auto &life = r->register_if_not_exist<component::Life>();
            auto &size = r->register_if_not_exist<component::Size>();
            auto &invincibility = r->register_if_not_exist<component::Invincibility>();

            for (std::size_t i = 0; i < position.size(); ++i) {
                if (!attribut[i] || !position[i] || !animation[i] || !size[i] || !destroyable[i] || !life[i] ||
                    (drawable[i] && !drawable[i]->_drawable)) {
                    continue;
                }

                if (attribut[i]->_entity_type == component::Attributes::EntityType::Background ||
                    destroyable[i]->_state != component::Destroyable::DestroyState::ALIVE) {
                    continue;
                }

                double i_width = animation[i]->_width * (size[i] ? size[i]->_width : 1.0);
                double i_height = animation[i]->_height * (size[i] ? size[i]->_height : 1.0);

                if ((position[i]->_x > WIDTH_MAX_LIMIT || position[i]->_x < WIDTH_MIN_LIMIT) ||
                    (position[i]->_y > HEIGHT_MAX_LIMIT || position[i]->_y < HEIGHT_MIN_LIMIT)) {
                    destroyable[i]->_state = component::Destroyable::DestroyState::WAITING;
                    continue;
                }

                for (std::size_t j = i + 1; j < position.size(); ++j) {
                    if (!attribut[j] || !position[j] || !size[j] || !destroyable[j] ||
                        destroyable[j]->_state != ecs::component::Destroyable::DestroyState::ALIVE || !life[j] ||
                        i == j || attribut[i]->_entity_type == attribut[j]->_entity_type ||
                        ((attribut[i]->_entity_type == attribut[j]->_entity_type) &&
                         (attribut[i]->_secondary_type == attribut[j]->_secondary_type))) {
                        continue;
                    }

                    double j_width = animation[j]->_width * (size[j] ? size[j]->_width : 1.0);
                    double j_height = animation[j]->_height * (size[j] ? size[j]->_height : 1.0);

                    if ((position[j]->_x > WIDTH_MAX_LIMIT || position[j]->_x < WIDTH_MIN_LIMIT) ||
                        (position[j]->_y > HEIGHT_MAX_LIMIT || position[j]->_y < HEIGHT_MIN_LIMIT)) {
                        destroyable[j]->_state = component::Destroyable::DestroyState::WAITING;
                        continue;
                    }

                    if ((attribut[i]->_entity_type == component::Attributes::EntityType::Weapon &&
                         attribut[i]->_secondary_type == component::Attributes::SecondaryType::None &&
                         attribut[j]->_entity_type == component::Attributes::EntityType::Player) ||
                        (attribut[j]->_entity_type == component::Attributes::EntityType::Weapon &&
                         attribut[j]->_secondary_type == component::Attributes::SecondaryType::None &&
                         attribut[i]->_entity_type == component::Attributes::EntityType::Player)) {
                        continue;
                    }

                    if ((attribut[i]->_entity_type == component::Attributes::EntityType::Weapon &&
                         attribut[i]->_secondary_type == component::Attributes::SecondaryType::Basic &&
                         attribut[j]->_entity_type == component::Attributes::EntityType::Ennemy) ||
                        (attribut[j]->_entity_type == component::Attributes::EntityType::Weapon &&
                         attribut[j]->_secondary_type == component::Attributes::SecondaryType::Basic &&
                         attribut[i]->_entity_type == component::Attributes::EntityType::Ennemy)) {
                        continue;
                    }

                    if (((position[i]->_x + i_width >= position[j]->_x && position[i]->_x <= position[j]->_x + j_width
                         ) &&
                         (position[i]->_y + i_height >= position[j]->_y && position[i]->_y <= position[j]->_y + j_height
                         )) &&
                        attribut[i]->_entity_type != attribut[j]->_entity_type) {

                        if (!invincibility[i].has_value()) {
                            life[i]->_life = life[i]->_life - 1;
                        }
                        if (!invincibility[j].has_value()) {
                            life[j]->_life = life[j]->_life - 1;
                        }

                        if (invincibility[i].has_value() && !invincibility[i]->_invincible) {
                            life[i]->_life = life[i]->_life - 1;
                            invincibility[i]->_invincible = true;
                            invincibility[i]->_clock.restart();
                        }
                        if (invincibility[j].has_value() && !invincibility[j]->_invincible) {
                            life[j]->_life = life[j]->_life - 1;
                            invincibility[j]->_invincible = true;
                            invincibility[j]->_clock.restart();
                        }

                        if (life[i]->_life <= 0) {
                            destroyable[i]->_state = component::Destroyable::DestroyState::WAITING;
                        }
                        if (life[j]->_life <= 0) {
                            destroyable[j]->_state = component::Destroyable::DestroyState::WAITING;
                        }

                        continue;
                    }
                }
            }
        }
    } // namespace systems
} // namespace ecs
