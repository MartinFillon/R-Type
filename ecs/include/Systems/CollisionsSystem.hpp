/*
** EPITECH PROJECT, 2024
** RType
** File description:
** CollisionsSystem
*/

#ifndef COLLISIONSSYSTEM_HPP_
#define COLLISIONSSYSTEM_HPP_

#define BLANK_SPRITE_SPACE 50

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

                for (std::size_t i = 0; i < position.size(); ++i) {
                    if (!position[i] || !animation[i] || (drawable[i] && !drawable[i]->_drawable)) {
                        continue;
                    }

                    if (animation[i]->_object == ecs::component::Object::Background) {
                        continue;
                    }

                    if ((position[i]->_x > 2000 || position[i]->_x < -100) ||
                        (position[i]->_y > 1080 || position[i]->_y < -100)) {
                        _entitiesToErase.push_back(i);
                        continue;
                    }

                    for (std::size_t j = i + 1; j < position.size(); ++j) {
                        if (!position[j] || i == j || animation[i]->_object == animation[j]->_object) {
                            continue;
                        }

                        if ((position[i]->_x + animation[i]->_width>= position[j]->_x &&
                             position[i]->_x <= position[j]->_x + animation[j]->_width) &&
                            (position[i]->_y + animation[i]->_height >= position[j]->_y &&
                             position[i]->_y <= position[j]->_y + animation[j]->_height + BLANK_SPRITE_SPACE)) {
                            _entitiesToErase.push_back(i);
                            _entitiesToErase.push_back(j);
                            break;
                        }
                    }
                }

                for (std::size_t idx : _entitiesToErase) {
                    if (idx < position.size()) {
                        r.erase(idx);
                    }
                }
            }
              private:
                std::vector<std::size_t> _entitiesToErase;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* COLLISIONSSYSTEM_HPP_ */
