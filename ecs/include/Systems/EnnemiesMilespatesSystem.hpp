/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnnemiesMilespatesSystem
*/

#ifndef ENNEMIESMILESPATESSYSTEM_HPP_
#define ENNEMIESMILESPATESSYSTEM_HPP_

#define NB_ENNEMIES 4
#define MILESPATES_SPEED 0.2
#define MILESPATES_SPRITE "r-typesheet8.gif"
#define HEIGHT_LIMIT 500
#define HEIGHT_MAX 1000

#include <vector>
#include <iostream>

#include "Components/Animations.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"
#include "Components/Position.hpp"
#include "Entity.hpp"
#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class EnnemiesMilespatesSystem : public ISystems {
            public:
                void createMilespates(Registry &r)
                {
                    std::vector<Entity> milespates;
                    int lastX = 1300;
                    int lastY = 80;

                    for (std::size_t i = 0; i < NB_ENNEMIES; ++i) {
                        milespates.push_back(r.spawn_entity());
                        r._entities.addEntity(milespates[i]);
                    }

                    auto &positions = r.get_components<ecs::component::Position>();
                    auto &drawables = r.get_components<ecs::component::Drawable>();
                    auto &controllable = r.get_components<ecs::component::Controllable>();
                    auto &sprites = r.get_components<ecs::component::Sprite>();
                    auto &animations = r.get_components<ecs::component::Animations>();
                    auto &sizes = r.get_components<ecs::component::Size>();
                    auto &destroyable = r.get_components<ecs::component::Destroyable>();

                    for (const auto &i: milespates) {
                        positions[i.getId()] = ecs::component::Position{lastX += 40, lastY += 60};
                        drawables[i.getId()] = ecs::component::Drawable{true};
                        controllable[i.getId()] = ecs::component::Controllable{false, MILESPATES_SPEED};
                        sprites[i.getId()] = ecs::component::Sprite{MILESPATES_SPRITE};
                        animations[i.getId()] =
                            ecs::component::Animations{ecs::Clock(), 30, 30, 0, 0, 0, ecs::component::Object::Milespates};
                        sizes[i.getId()] = ecs::component::Size{2.8, 2.8};
                        destroyable[i.getId()] = ecs::component::Destroyable{false};
                    }
                }

                int countMilespates(Registry &r)
                {
                    auto &animations = r.get_components<ecs::component::Animations>();
                    int nbMilespates = 0;

                    for (auto &&[anim] : ecs::custom_zip(animations)) {
                        if (!anim) {
                            continue;
                        }

                        if (anim->_object == ecs::component::Object::Milespates) {
                            nbMilespates += 1;
                        }
                    }
                    std::cout << "milespates :" << nbMilespates << "\n";
                    return nbMilespates;
                }

                void operator()(Registry &r)
                {
                    if (countMilespates(r) == 0) {
                        createMilespates(r);
                        return;
                    }
                    auto &positions = r.get_components<ecs::component::Position>();
                    auto &drawables = r.get_components<ecs::component::Drawable>();
                    auto &controllable = r.get_components<ecs::component::Controllable>();
                    auto &sprites = r.get_components<ecs::component::Sprite>();
                    auto &animations = r.get_components<ecs::component::Animations>();
                    auto &sizes = r.get_components<ecs::component::Size>();

                    for (auto &&[pos, anim] : ecs::custom_zip(positions, animations)) {
                        if (!pos || !anim || anim->_object != ecs::component::Milespates) {
                            continue;
                        }
                        if (pos->_x > HEIGHT_MAX) {
                            pos->_x -= 10;
                            pos->_y += 10;
                        } else if (pos->_x < HEIGHT_LIMIT) {
                            pos->_x -= 10;
                            pos->_y -= 10;
                        }
                    }
                }
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !ENNEMIESMILESPATESSYSTEM_HPP_ */
