/*
** EPITECH PROJECT, 2024
** RType
** File description:
** CollisionsSystem
*/

#ifndef COLLISIONSSYSTEM_HPP_
#define COLLISIONSSYSTEM_HPP_

#define BLANK_SPRITE_SPACE 50

#include "Components/Destroyable.hpp"
#include "Components/Animations.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"

#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class CollisionsSystem {
          public:
            void operator()(Registry &r)
            {
                auto &position = r.get_components<ecs::component::Position>();
                auto &drawable = r.get_components<ecs::component::Drawable>();
                auto &animation = r.get_components<ecs::component::Animations>();
                auto &destroyable = r.get_components<ecs::component::Destroyable>();

                for (std::size_t i = 0; i < position.size(); ++i) {
                    if (!position[i] || !destroyable[i] || !animation[i] || (drawable[i] && !drawable[i]->_drawable)) {
                        continue;
                    }

                    if (animation[i]->_object == ecs::component::Object::Background) {
                        continue;
                    }

                    if ((position[i]->_x > 2000 || position[i]->_x < -300) ||
                        (position[i]->_y > 1080 || position[i]->_y < -300)) {
                            destroyable[i]->_destroyable = true;
                            if (animation[i]->_object == ecs::component::Object::Weapon) {
                                r.erase(i);
                            } else {
                               animation[i]->_object = ecs::component::Object::InDestroy;
                            }
                            continue;
                    }

                    for (std::size_t j = i + 1; j < position.size(); ++j) {
                        if (!position[j] || i == j || animation[i]->_object == animation[j]->_object) {
                            continue;
                        }

                        if ((position[j]->_x > 2000 || position[j]->_x < -300) ||
                            (position[j]->_y > 1080 || position[j]->_y < -300)) {
                                destroyable[j]->_destroyable = true;
                                if (animation[j]->_object == ecs::component::Object::Weapon) {
                                    r.erase(j);
                                } else {
                                   animation[j]->_object = ecs::component::Object::InDestroy;
                                }
                                continue;
                        }

                        if ((position[i]->_x + animation[i]->_width >= position[j]->_x &&
                             position[i]->_x <= position[j]->_x + animation[j]->_width) &&
                            (position[i]->_y + animation[i]->_height >= position[j]->_y &&
                             position[i]->_y <= position[j]->_y + animation[j]->_height + BLANK_SPRITE_SPACE)) {
                                destroyable[i]->_destroyable = true;
                                if (animation[i]->_object == ecs::component::Object::Weapon) {
                                    r.erase(i);
                                } else {
                                   animation[i]->_object = ecs::component::Object::InDestroy;
                                }
                                destroyable[j]->_destroyable = true;
                                if (animation[j]->_object == ecs::component::Object::Weapon) {
                                    r.erase(j);
                                } else {
                                   animation[j]->_object = ecs::component::Object::InDestroy;
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
