/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BossSystems
*/

#ifndef BOSSSYSTEMS_HPP_
#define BOSSSYSTEMS_HPP_

#define BOSS_LIFE(x) 100 * x
#define BOSS_SPEED 5
#define BOSS_SPAWN_TIME 60
#define BOSS_PROJECTILE_SPEED 5
#define BOSS_PROJECTILE_SPAWN_TIME 0.05
#define BOSS_SHOOTING_ELAPSED_TIME 0.5

#define PROJECTILE_CLOSE 200
#define PROJECTILE_PADDING 100

#include <functional>
#include <array>
#include <cmath>

#include "ZipperIterator.hpp"
#include "Clock.hpp"
#include "Components/Animations.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Life.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class BossSystems : public ISystems {
            public:
                void createNewProjectile(Registry &r, const ecs::component::Position &bossPos)
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
                    auto &life = r.get_components<ecs::component::Life>();

                    life[newProjectile.getId()] = ecs::component::Life{1};
                    positions[newProjectile.getId()] = ecs::component::Position{bossPos._x, bossPos._y, false};
                    drawables[newProjectile.getId()] = ecs::component::Drawable{true};
                    controllables[newProjectile.getId()] = ecs::component::Controllable{true, BOSS_PROJECTILE_SPEED};
                    sprites[newProjectile.getId()] = ecs::component::Sprite{ENNEMIES_WEAPON_SPRITE};
                    destroyable[newProjectile.getId()] = ecs::component::Destroyable{false};
                    animations[newProjectile.getId()] =
                        ecs::component::Animations{
                            ecs::Clock(),
                            20,
                            18,
                            0,
                            0,
                            0,
                            ecs::component::Object::Weapon,
                            ecs::component::Type::Boss
                        };
                    sizes[newProjectile.getId()] = ecs::component::Size{3, 3};
                }

                void createFirstBoss(Registry &r)
                {
                    Entity bossEntity = r.spawn_entity();
                    r._entities.addEntity(bossEntity);

                    auto &positions = r.get_components<ecs::component::Position>();
                    auto &drawables = r.get_components<ecs::component::Drawable>();
                    auto &controllables = r.get_components<ecs::component::Controllable>();
                    auto &sprites = r.get_components<ecs::component::Sprite>();
                    auto &animations = r.get_components<ecs::component::Animations>();
                    auto &sizes = r.get_components<ecs::component::Size>();
                    auto &destroyable = r.get_components<ecs::component::Destroyable>();
                    auto &life = r.get_components<ecs::component::Life>();

                    positions[bossEntity.getId()] = ecs::component::Position{2000, 1080 - 127 * 4, false};
                    drawables[bossEntity.getId()] = ecs::component::Drawable{true};
                    controllables[bossEntity.getId()] = ecs::component::Controllable{false, BOSS_SPEED};
                    sprites[bossEntity.getId()] = ecs::component::Sprite{FIRST_BOSS_SPRITE};
                    animations[bossEntity.getId()] = ecs::component::Animations{
                        Clock(),
                        255,
                        127,
                        260,
                        0,
                        0,
                        ecs::component::Object::Ennemies,
                        ecs::component::Type::Boss
                    };
                    sizes[bossEntity.getId()] = ecs::component::Size{4, 4};
                    destroyable[bossEntity.getId()] = ecs::component::Destroyable{false};
                    life[bossEntity.getId()] = ecs::component::Life{2};
                }

                bool isABoss(Registry &r)
                {
                    auto &animations = r.get_components<ecs::component::Animations>();

                    for (auto &&[anim] : custom_zip(animations)) {
                        if (!anim) {
                            continue;
                        }
                        if (anim->_object == ecs::component::Object::Ennemies && anim->_type == ecs::component::Type::Boss) {
                            return true;
                        }
                    }

                    return false;
                }

                void moveProjectileTowardsPlayer(Registry &r, ecs::component::Position &projectilePos, const std::size_t &idx)
                {
                    auto &positions = r.get_components<ecs::component::Position>();
                    ecs::component::Position playerPos = {0, 0};

                    for (std::size_t i = 0; i < positions.size(); ++i) {
                        if (positions[i] && r.get_components<ecs::component::Animations>()[i]->_object == ecs::component::Object::Player) {
                            playerPos._x = positions[i]->_x;
                            playerPos._y = positions[i]->_y;
                            break;
                        }
                    }

                    if (playerPos._x == 0.0 && playerPos._y == 0.0) {
                        return;
                    }

                    float distance = std::sqrt(std::pow(projectilePos._x - playerPos._x, 2) + std::pow(projectilePos._y - playerPos._y, 2));

                    if (distance <= PROJECTILE_CLOSE) {
                        auto &destroyables = r.get_components<ecs::component::Destroyable>();
                        destroyables[idx]->_destroyable = true;
                        return;
                    }

                    int targetX = playerPos._x;
                    int targetY = playerPos._y;

                    if (projectilePos._x < targetX) {
                        projectilePos._x += BOSS_PROJECTILE_SPEED;
                    } else if (projectilePos._x > targetX) {
                        projectilePos._x -= BOSS_PROJECTILE_SPEED;
                    }

                    if (projectilePos._y < targetY) {
                        projectilePos._y += BOSS_PROJECTILE_SPEED;
                    } else if (projectilePos._y > targetY) {
                        projectilePos._y -= BOSS_PROJECTILE_SPEED;
                    }
                }

                void operator()(Registry &r)
                {
                    bool isBoss = isABoss(r);

                    if (_bossClock.getSeconds() < BOSS_SPAWN_TIME && !isBoss) {
                        return;
                    }

                    if (!isBoss && times < _bosses.size()) {
                        auto createBossFunction = _bosses[times];
                        createBossFunction(r);
                        times += 1;
                    }

                    auto &positions = r.get_components<ecs::component::Position>();
                    auto &controllables = r.get_components<ecs::component::Controllable>();
                    auto &animations = r.get_components<ecs::component::Animations>();
                    auto &lifes = r.get_components<ecs::component::Life>();
                    auto &destroyables = r.get_components<ecs::component::Destroyable>();
                    int idx = 0;

                    for (auto &&[pos, control, anim, life, destroyable] : custom_zip(positions, controllables, animations, lifes, destroyables)) {
                        if (!pos || !control || !anim || !life || !destroyable) {
                            idx += 1;
                            continue;
                        }

                        if (anim->_type == ecs::component::Type::Basic || anim->_type == ecs::component::Type::Milespates) {
                            destroyable->_destroyable = true;
                        }

                        if (anim->_type != ecs::component::Type::Boss) {
                            idx += 1;
                            continue;
                        }

                        if (anim->_object == ecs::component::Weapon &&
                            _projectileClock.getSeconds() > 0.01) {
                                moveProjectileTowardsPlayer(r, *pos, idx);
                                _projectileClock.restart();
                                continue;
                        }

                        if (_shootingClock.getSeconds() > BOSS_PROJECTILE_SPAWN_TIME) {
                            createNewProjectile(r, *pos);
                            _shootingClock.restart();
                        }

                        if (life->_life <= 0) {
                            destroyable->_destroyable = true;
                            break;
                        }

                        if (anim->_clock.getMiliSeconds() > 10 && pos->_x >= 1000) {
                            pos->_x -= control->_speed;
                            anim->_clock.restart();
                        }
                        idx += 1;
                    }
                }

            private:
                ecs::Clock _bossClock;
                ecs::Clock _shootingClock;
                ecs::Clock _projectileClock;
                std::size_t times = 0;
                std::array<std::function<void (Registry &r)>, 4> _bosses {
                    {[this](Registry &r){createFirstBoss(r);}},
                };
        };
    } // namespace systems
} // namespace ecs

#endif /* !BOSSSYSTEMS_HPP_ */
