/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionsSystem
*/

#ifndef COLLISIONSSYSTEM_HPP_
#define COLLISIONSSYSTEM_HPP_

#define WIDTH_MAX_LIMIT 2700
#define HEIGHT_MAX_LIMIT 2500

#define WIDTH_MIN_LIMIT -300
#define HEIGHT_MIN_LIMIT -300

#include "Systems/ISystems.hpp"
#include "Components/Life.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Animations.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class CollisionsSystem : public ISystems {
            public:

            void operator()(Registry &r)
            {
                auto &position = r.get_components<ecs::component::Position>();
                auto &drawable = r.get_components<ecs::component::Drawable>();
                auto &animation = r.get_components<ecs::component::Animations>();
                auto &destroyable = r.get_components<ecs::component::Destroyable>();
                auto &life = r.get_components<ecs::component::Life>();
                auto &size = r.get_components<ecs::component::Size>();

                for (std::size_t i = 0; i < position.size(); ++i) {
                    if (!position[i] || !size[i] || !destroyable[i] || !life[i] || !animation[i] || (drawable[i] && !drawable[i]->_drawable)) {
                        continue;
                    }

                    if (animation[i]->_object == ecs::component::Object::Background) {
                        continue;
                    }

                    double i_width = animation[i]->_width * (size[i] ? size[i]->_width : 1.0);
                    double i_height = animation[i]->_height * (size[i] ? size[i]->_height : 1.0);

                    if ((position[i]->_x > WIDTH_MAX_LIMIT || position[i]->_x < WIDTH_MIN_LIMIT) ||
                        (position[i]->_y > HEIGHT_MAX_LIMIT || position[i]->_y < HEIGHT_MIN_LIMIT)) {
                            if (animation[i]->_object == ecs::component::Object::Weapon) {
                                r.erase(i);
                            } else {
                                destroyable[i]->_destroyable = true;
                                animation[i]->_object = ecs::component::Object::InDestroy;
                            }
                            continue;
                    }

                    for (std::size_t j = i + 1; j < position.size(); ++j) {
                        if (!position[j] || !size[j] || !life[j] || i == j || animation[i]->_object == animation[j]->_object) {
                            continue;
                        }

                        double j_width = animation[j]->_width * (size[j] ? size[j]->_width : 1.0);
                        double j_height = animation[j]->_height * (size[j] ? size[j]->_height : 1.0);

                        if ((position[j]->_x > WIDTH_MAX_LIMIT || position[j]->_x < WIDTH_MIN_LIMIT) ||
                            (position[j]->_y > HEIGHT_MAX_LIMIT || position[j]->_y < HEIGHT_MIN_LIMIT)) {
                                if (animation[j]->_object == ecs::component::Object::Weapon) {
                                    r.erase(j);
                                } else {
                                    destroyable[j]->_destroyable = true;
                                    animation[j]->_object = ecs::component::Object::InDestroy;
                                }
                                continue;
                        }

                        if ((animation[i]->_type == ecs::component::Type::Milespates &&
                            animation[i]->_object == ecs::component::Object::InDestroy) ||
                            (animation[j]->_object == ecs::component::Object::InDestroy &&
                            animation[j]->_type == ecs::component::Type::Milespates)) {
                            continue;
                        }

                        if ((animation[i]->_object == ecs::component::Object::Weapon ||
                            animation[j]->_object == ecs::component::Object::Weapon) &&
                            (animation[j]->_type != ecs::component::Type::None &&
                            animation[i]->_type != ecs::component::Type::None)) {
                            continue;
                        }

                        if (((position[i]->_x + i_width >= position[j]->_x &&
                             position[i]->_x <= position[j]->_x + j_width) &&
                            (position[i]->_y + i_height >= position[j]->_y &&
                             position[i]->_y <= position[j]->_y + j_height)) &&
                             animation[i]->_object != animation[j]->_object) {

                            life[i]->_life -= 1;
                            life[j]->_life -= 1;

                            if (animation[i]->_object == ecs::component::Object::Player && life[i]->_life > 0) {
                                position[i]->_x = 100;
                                position[i]->_y = 100;
                            }

                            if (animation[j]->_object == ecs::component::Object::Player && life[j]->_life > 0) {
                                position[j]->_x = 100;
                                position[j]->_y = 100;
                            }

                            if (animation[i]->_object == ecs::component::Object::Weapon) {
                                r.erase(i);
                            } else {
                                if (life[i]->_life <= 0) {
                                    destroyable[i]->_destroyable = true;
                                    animation[i]->_object = ecs::component::Object::InDestroy;
                                }
                            }

                            if (animation[j]->_object == ecs::component::Object::Weapon) {
                                r.erase(j);
                            } else {
                                if (life[j]->_life <= 0) {
                                    destroyable[j]->_destroyable = true;
                                    animation[j]->_object = ecs::component::Object::InDestroy;
                                }
                            }

                            continue;
                        }
                    }
                }
            }
        };
    }; // namespace systems
}; // namespace ecs

#endif /* COLLISIONSSYSTEM_HPP_ */
