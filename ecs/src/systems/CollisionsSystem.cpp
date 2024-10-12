/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** Collision system file
*/

#include "Systems/CollisionsSystem.hpp"
#include "Components/Animations.hpp"
#include "Components/Life.hpp"

namespace ecs {
    namespace systems {
        void CollisionsSystem::operator()(Registry &r, std::shared_ptr<IContext> ctx)
        {
            auto &position = r.register_if_not_exist<component::Position>();
            auto &drawable = r.register_if_not_exist<component::Drawable>();
            auto &animation = r.register_if_not_exist<component::Animations>();
            auto &destroyable = r.register_if_not_exist<component::Destroyable>();
            auto &life = r.register_if_not_exist<component::Life>();
            auto &size = r.register_if_not_exist<component::Size>();

            for (std::size_t i = 0; i < position.size(); ++i) {
                if (!position[i] || !size[i] || !destroyable[i] || !life[i] || !animation[i] ||
                    (drawable[i] && !drawable[i]->_drawable)) {
                    continue;
                }

                if (animation[i]->_object == component::Object::Background ||
                    animation[i]->_object == component::Object::InDestroy) {
                    continue;
                }

                double i_width = animation[i]->_width * (size[i] ? size[i]->_width : 1.0);
                double i_height = animation[i]->_height * (size[i] ? size[i]->_height : 1.0);

                if ((position[i]->_x > WIDTH_MAX_LIMIT || position[i]->_x < WIDTH_MIN_LIMIT) ||
                    (position[i]->_y > HEIGHT_MAX_LIMIT || position[i]->_y < HEIGHT_MIN_LIMIT)) {
                    if (animation[i]->_object == component::Object::Weapon) {
                        r.erase(i);
                    } else {
                        destroyable[i]->_destroyable = true;
                        animation[i]->_object = component::Object::InDestroy;
                    }
                    sendDestroyedObject(ctx, i);
                    continue;
                }

                for (std::size_t j = i + 1; j < position.size(); ++j) {
                    if (!position[j] || !size[j] || !life[j] || i == j ||
                        animation[i]->_object == animation[j]->_object) {
                        continue;
                    }

                    double j_width = animation[j]->_width * (size[j] ? size[j]->_width : 1.0);
                    double j_height = animation[j]->_height * (size[j] ? size[j]->_height : 1.0);

                    if ((position[j]->_x > WIDTH_MAX_LIMIT || position[j]->_x < WIDTH_MIN_LIMIT) ||
                        (position[j]->_y > HEIGHT_MAX_LIMIT || position[j]->_y < HEIGHT_MIN_LIMIT)) {
                        if (animation[j]->_object == component::Object::Weapon) {
                            r.erase(j);
                        } else {
                            destroyable[j]->_destroyable = true;
                            animation[j]->_object = component::Object::InDestroy;
                        }
                        sendDestroyedObject(ctx, j);
                        continue;
                    }

                    if ((animation[i]->_type == component::Type::Milespates &&
                         animation[i]->_object == component::Object::InDestroy) ||
                        (animation[j]->_object == component::Object::InDestroy &&
                         animation[j]->_type == component::Type::Milespates)) {
                        continue;
                    }

                    if ((animation[i]->_object == component::Object::Weapon ||
                         animation[j]->_object == component::Object::Weapon) &&
                        (animation[j]->_type != component::Type::None && animation[i]->_type != component::Type::None
                        )) {
                        continue;
                    }
                    if ((animation[i]->_object == component::Object::Weapon && animation[i]->_type == component::Type::None &&
                        animation[j]->_object == component::Object::Player) ||
                        (animation[j]->_object == component::Object::Weapon && animation[j]->_type == component::Type::None &&
                        animation[i]->_object == component::Object::Player)) {
                            continue;
                        }

                    if (((position[i]->_x + i_width >= position[j]->_x && position[i]->_x <= position[j]->_x + j_width
                         ) &&
                         (position[i]->_y + i_height >= position[j]->_y && position[i]->_y <= position[j]->_y + j_height
                         )) &&
                        animation[i]->_object != animation[j]->_object) {

                        life[i]->_life -= 1;
                        life[j]->_life -= 1;

                        if (animation[i]->_object == component::Object::Player && life[i]->_life > 0) {
                            position[i]->_x = 100;
                            position[i]->_y = 100;
                        }

                        if (animation[j]->_object == component::Object::Player && life[j]->_life > 0) {
                            position[j]->_x = 100;
                            position[j]->_y = 100;
                        }

                        if (animation[i]->_object == component::Object::Weapon) {
                            r.erase(i);
                            sendDestroyedObject(ctx, i);
                        } else {
                            if (life[i]->_life <= 0) {
                                destroyable[i]->_destroyable = true;
                                animation[i]->_object = component::Object::InDestroy;
                                sendDestroyedObject(ctx, i);
                            }
                        }

                        if (animation[j]->_object == component::Object::Weapon) {
                            r.erase(j);
                            sendDestroyedObject(ctx, j);
                        } else {
                            if (life[j]->_life <= 0) {
                                destroyable[j]->_destroyable = true;
                                animation[j]->_object = component::Object::InDestroy;
                                sendDestroyedObject(ctx, j);
                            }
                        }
                        continue;
                    }
                }
            }
        }

        void CollisionsSystem::sendDestroyedObject(std::shared_ptr<IContext> &ctx, std::size_t i)
        {
            if (ctx) {
                ctx->destroyObject(i);
            }
        }
    } // namespace systems
} // namespace ecs
