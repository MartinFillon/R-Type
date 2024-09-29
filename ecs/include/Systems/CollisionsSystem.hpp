/*
** EPITECH PROJECT, 2024
** RType
** File description:
** CollisionsSystem
*/

#ifndef COLLISIONSSYSTEM_HPP_
#define COLLISIONSSYSTEM_HPP_

#include "Components/Animations.hpp"
#include "Components/Position.hpp"
#include "Components/Parallax.hpp"
#include "Components/Sprite.hpp"
#include "Components/Drawable.hpp"
#include "Components/Size.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class CollisionsSystem {
          public:
            void operator()(Registry &r)
            {
                auto &position = r.get_components<ecs::component::Position>();
                auto &drawable = r.get_components<ecs::component::Drawable>();
                auto &sprite = r.get_components<ecs::component::Sprite>();
                auto &animation = r.get_components<ecs::component::Animations>();
                auto &parallax = r.get_components<ecs::component::Parallax>();
                auto &size = r.get_components<ecs::component::Size>();

                std::vector<std::size_t> entitiesToErase;

                for (std::size_t i = 0; i < position.size(); ++i) {
                    if (!position[i] || !animation[i]) {
                        continue;
                    }

                    if (animation[i]->_object == ecs::component::Object::Background) {
                        continue;
                    }

                    if (animation[i]->_object == ecs::component::Object::Player) {
                        std::cout << "player x: " << position[i]->_x << " y: " << position[i]->_y << "\n";
                    }

                    if ((position[i]->_x > 2000 || position[i]->_x < 0) ||
                        (position[i]->_y > 1080 || position[i]->_y < 0)) {
                        std::cout << "rm: " << i << "\n";
                        drawable[i]->_drawable = false;
                        entitiesToErase.push_back(i);
                        continue;
                    }

                    for (std::size_t j = i + 1; j < position.size(); ++j) {
                        if (!position[j] || i == j) {
                            continue;
                        }

                        if (position[i]->_x == position[j]->_x && position[i]->_y == position[j]->_y) {
                            std::cout << "collision on " << i << " and " << j << "\n";
                            drawable[i]->_drawable = false;
                            drawable[j]->_drawable = false;
                            entitiesToErase.push_back(i);
                            entitiesToErase.push_back(j);
                            break;
                        }
                    }
                }

                /*std::sort(entitiesToErase.begin(), entitiesToErase.end(), std::greater<>());
                for (std::size_t idx : entitiesToErase) {
                    if (idx < position.size()) {
                        position.erase(idx);
                        drawable.erase(idx);
                        sprite.erase(idx);
                        animation.erase(idx);
                        parallax.erase(idx);
                        size.erase(idx);
                        r._entitys.erase(idx);
                    }
                }*/
            }
        };
    }; // namespace systems
}; // namespace ecs

#endif /* COLLISIONSSYSTEM_HPP_ */
