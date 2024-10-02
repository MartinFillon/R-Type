/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** basicRandomEnnemiesSystem
*/

#ifndef BASICRANDOMENNEMIESSYSTEM_HPP_
#define BASICRANDOMENNEMIESSYSTEM_HPP_

#include "Clock.hpp"
#define MAX_RANDOM_ENNEMIES 7
#define VALUE_SPAWN_ENNEMIES 2
#define BASIC_ENNEMIES_ANIMATON_SPEED 0.24
#define BASIC_ENNEMIES_SPEED 1.8

#ifdef _WIN32
    #include <array>
#endif

#include <random>

#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"

#include "ISystems.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

namespace ecs {
    namespace systems {
        class BasicRandomEnnemiesSystem : public ISystems {
          public:
            void createNewEnnemies(Registry &r)
            {

                std::random_device randomPosition;
                std::default_random_engine randomEngine(randomPosition());
                std::uniform_int_distribution<int> uniform_dist(100, 400);
                double randomPosY = uniform_dist(randomEngine);

                Entity newEnnemies = r.spawn_entity();
                r._entities.addEntity(newEnnemies);
                auto &positions = r.get_components<ecs::component::Position>();
                auto &drawables = r.get_components<ecs::component::Drawable>();
                auto &controllable = r.get_components<ecs::component::Controllable>();
                auto &sprites = r.get_components<ecs::component::Sprite>();
                auto &animations = r.get_components<ecs::component::Animations>();
                auto &sizes = r.get_components<ecs::component::Size>();
                positions[newEnnemies.getId()] = ecs::component::Position{1944, randomPosY};
                drawables[newEnnemies.getId()] = ecs::component::Drawable{true};
                controllable[newEnnemies.getId()] = ecs::component::Controllable{false, BASIC_ENNEMIES_SPEED};
                sprites[newEnnemies.getId()] = ecs::component::Sprite{BASIC_ENNEMIES_SPRITE};
                animations[newEnnemies.getId()] =
                    ecs::component::Animations{ecs::Clock(), 32, 35, 224, 0, 0, ecs::component::Object::Ennemies};
                sizes[newEnnemies.getId()] = ecs::component::Size{2.8, 2.8};
            }

            int nbOfBasicEnnemies(Registry &r)
            {
                int nbOfEnnemies = 0;
                auto &animations = r.get_components<ecs::component::Animations>();

                for (std::size_t i = 0; i < animations.size(); ++i) {
                    if (animations[i] && animations[i]->_object == ecs::component::Object::Ennemies) {
                        nbOfEnnemies += 1;
                    }
                }

                return nbOfEnnemies;
            }

            void operator()(Registry &r)
            {
                if (nbOfBasicEnnemies(r) < MAX_RANDOM_ENNEMIES) {
                    createNewEnnemies(r);
                }

                auto &animations = r.get_components<ecs::component::Animations>();
                auto &positions = r.get_components<ecs::component::Position>();
                auto &controllable = r.get_components<ecs::component::Controllable>();

                for (auto &&[anim, pos, ctrl] : ecs::custom_zip(animations, positions, controllable)) {
                    if (!anim || !pos || !ctrl) {
                        continue;
                    }
                    if (anim->_object == ecs::component::Object::Ennemies) {
                        if (anim->_x <= 0 && anim->_x != 224) {
                            anim->_x = 224;
                        }
                        if (anim->_x > 0 && anim->_clock.getSeconds() > 0.3) {
                            anim->_x -= anim->_width;
                            anim->_clock.restart();
                        }
                        if (anim->_clock.getMiliSeconds() > 0.3) {
                            pos->_x -= ctrl->_speed;
                        }
                    }
                }
            }
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !BASICRANDOMENNEMIESSYSTEM_HPP_ */
