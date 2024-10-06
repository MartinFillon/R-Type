#ifndef BASICRANDOMENNEMIESSYSTEM_HPP_
#define BASICRANDOMENNEMIESSYSTEM_HPP_

#include "Clock.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Life.hpp"

#define MAX_RANDOM_ENNEMIES 7
#define VALUE_SPAWN_ENNEMIES 2
#define BASIC_ENNEMIES_ANIMATON_SPEED 0.24
#define BASIC_ENNEMIES_SPEED 1.8
#define BASIC_ENNEMIES_PROJECTILE_SPEED 10
#define CENTERED_SHOOT 15

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

            void createNewProjectile(Registry &r, const ecs::component::Position &ennemiesPos)
            {
                Entity newProjectile = r.spawn_entity();
                r._entities.addEntity(newProjectile);
                auto &positions = r.get_components<ecs::component::Position>();
                auto &drawables = r.get_components<ecs::component::Drawable>();
                auto &controllables = r.get_components<ecs::component::Controllable>();
                auto &sprites = r.get_components<ecs::component::Sprite>();
                auto &animations = r.get_components<ecs::component::Animations>();
                auto &sizes = r.get_components<ecs::component::Size>();
                auto &destroyable = r.get_components<ecs::component::Destroyable>();

                positions[newProjectile.getId()] = ecs::component::Position{ennemiesPos._x, ennemiesPos._y + CENTERED_SHOOT};
                drawables[newProjectile.getId()] = ecs::component::Drawable{true};
                controllables[newProjectile.getId()] = ecs::component::Controllable{true, BASIC_ENNEMIES_PROJECTILE_SPEED};
                sprites[newProjectile.getId()] = ecs::component::Sprite{ENNEMIES_WEAPON_SPRITE};
                destroyable[newProjectile.getId()] = ecs::component::Destroyable{false};
                animations[newProjectile.getId()] =
                ecs::component::Animations {
                    ecs::Clock(),
                    20,
                    18,
                    0,
                    0,
                    0,
                    ecs::component::Object::Weapon,
                    ecs::component::Type::Basic
                };
                sizes[newProjectile.getId()] = ecs::component::Size{3, 3};
            }

            void createNewEnnemies(Registry &r)
            {
                std::random_device randomPosition;
                std::default_random_engine randomEngine(randomPosition());
                std::uniform_int_distribution<int> uniform_dist(100, 800);
                int randomPosY = uniform_dist(randomEngine);

                Entity newEnnemies = r.spawn_entity();
                r._entities.addEntity(newEnnemies);
                auto &positions = r.get_components<ecs::component::Position>();
                auto &drawables = r.get_components<ecs::component::Drawable>();
                auto &controllable = r.get_components<ecs::component::Controllable>();
                auto &sprites = r.get_components<ecs::component::Sprite>();
                auto &animations = r.get_components<ecs::component::Animations>();
                auto &sizes = r.get_components<ecs::component::Size>();
                auto &destroyable = r.get_components<ecs::component::Destroyable>();
                auto &life = r.get_components<ecs::component::Life>();

                life[newEnnemies.getId()] = ecs::component::Life{1};
                positions[newEnnemies.getId()] = ecs::component::Position{1944, randomPosY, false};
                drawables[newEnnemies.getId()] = ecs::component::Drawable{true};
                controllable[newEnnemies.getId()] = ecs::component::Controllable{false, BASIC_ENNEMIES_SPEED};
                sprites[newEnnemies.getId()] = ecs::component::Sprite{BASIC_ENNEMIES_SPRITE};
                animations[newEnnemies.getId()] =
                    ecs::component::Animations{
                        ecs::Clock(),
                        32,
                        35,
                        224,
                        0,
                        0,
                        ecs::component::Object::Ennemies,
                        ecs::component::Type::Basic};
                sizes[newEnnemies.getId()] = ecs::component::Size{2.8, 2.8};
                destroyable[newEnnemies.getId()] = ecs::component::Destroyable{false};
            }

            int nbOfBasicEnnemies(Registry &r)
            {
                int nbOfEnnemies = 0;
                auto &animations = r.get_components<ecs::component::Animations>();

                for (std::size_t i = 0; i < animations.size(); ++i) {
                    if (animations[i] && animations[i]->_type == ecs::component::Type::Basic) {
                        nbOfEnnemies += 1;
                    }
                }

                return nbOfEnnemies;
            }

            void shootRandomly(Registry &r, ecs::component::Position &enemyPos)
            {
                std::random_device randomDevice;
                std::default_random_engine randomEngine(randomDevice());
                std::uniform_int_distribution<int> shootChance(0, 100);

                if (shootChance(randomEngine) < 1) {
                    createNewProjectile(r, enemyPos);
                }
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
                    if (!anim || !pos || !ctrl ||
                        anim->_type != ecs::component::Type::Basic) {
                        continue;
                    }

                    if (anim->_object == ecs::component::Object::Weapon) {
                        pos->_x -= ctrl->_speed;
                        continue;
                    }

                    if (anim->_object != ecs::component::Object::Ennemies) {
                        continue;
                    }

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

                    shootRandomly(r, *pos);
                }
            }
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !BASICRANDOMENNEMIESSYSTEM_HPP_ */
