/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** basicRandomEnnemiesSystem
*/

#ifndef BASICRANDOMENNEMIESSYSTEM_HPP_
#define BASICRANDOMENNEMIESSYSTEM_HPP_

#define RANDOM_POS_ARR_SIZE 7
#define MAX_RANDOM_ENNEMIES 7
#define VALUE_SPAWN_ENNEMIES 2

#ifdef _WIN32
    #include <array>
#endif

#include <cmath>
#include <random>

#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class BasicRandomEnnemiesSystem : public ISystems {
          public:
            std::array<std::pair<double, bool>, RANDOM_POS_ARR_SIZE> _positions{
                std::make_pair<double, bool>(100, true),
                std::make_pair<double, bool>(145, true),
                std::make_pair<double, bool>(190, true),
                std::make_pair<double, bool>(235, true),
                std::make_pair<double, bool>(280, true),
                std::make_pair<double, bool>(325, true),
                std::make_pair<double, bool>(370, true)
            };

            void createNewEnnemies(Registry &r)
            {

                std::random_device randomPosition;
                std::default_random_engine randomEngine(randomPosition());
                std::uniform_int_distribution<int> uniform_dist(0, RANDOM_POS_ARR_SIZE);
                int randomPosY = uniform_dist(randomEngine);

                if (!_positions[randomPosY].second) {
                    createNewEnnemies(r);
                } else {
                    _positions[randomPosY].second = false;
                }

                Entity newEnnemies = r.spawn_entity();
                r._entitys.addEntity(newEnnemies);
                auto &positions = r.get_components<ecs::component::Position>();
                auto &drawables = r.get_components<ecs::component::Drawable>();
                auto &controllable = r.get_components<ecs::component::Controllable>();
                auto &sprites = r.get_components<ecs::component::Sprite>();
                auto &animations = r.get_components<ecs::component::Animations>();
                auto &sizes = r.get_components<ecs::component::Size>();
                positions[newEnnemies.getId()] = ecs::component::Position{1944, _positions[randomPosY].first};
                drawables[newEnnemies.getId()] = ecs::component::Drawable{true};
                controllable[newEnnemies.getId()] = ecs::component::Controllable{false, 2.5};
                sprites[newEnnemies.getId()] = ecs::component::Sprite{BASIC_ENNEMIES_SPRITE};
                animations[newEnnemies.getId()] =
                    ecs::component::Animations{sf::Clock(), 32, 35, 224, 0, 0, ecs::component::Object::Ennemies};
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
                std::random_device isEnemmyCanSpawn;

                std::default_random_engine randomEngine(isEnemmyCanSpawn());
                std::uniform_int_distribution<int> uniform_dist(0, 100);
                int mean = uniform_dist(randomEngine);

                if (nbOfBasicEnnemies(r) < MAX_RANDOM_ENNEMIES && mean == VALUE_SPAWN_ENNEMIES) {
                    createNewEnnemies(r);
                }

                auto &animations = r.get_components<ecs::component::Animations>();
                auto &positions = r.get_components<ecs::component::Position>();
                auto &controllable = r.get_components<ecs::component::Controllable>();

                for (std::size_t i = 0; i < animations.size(); ++i) {
                    if (animations[i] && animations[i]->_object == ecs::component::Object::Ennemies) {
                        if (animations[i]->_x <= 0 && animations[i]->_x != 224) {
                            animations[i]->_x = 224;
                            animations[i]->_clock.restart();
                        }
                        if (animations[i]->_x > 0 && animations[i]->_clock.getElapsedTime().asSeconds() > 0.3) {
                            animations[i]->_x -= animations[i]->_width;
                            animations[i]->_clock.restart();
                        }
                        positions[i]->_x -= controllable[i]->_speed;
                    }
                }
            }
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !BASICRANDOMENNEMIESSYSTEM_HPP_ */
