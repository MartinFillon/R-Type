/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** EnnemiesMilepatesSystem
*/

#include <memory>

#include "ComponentFactory.hpp"
#include "IContext.hpp"
#include "Registry.hpp"
#include "Systems/EnnemiesMilepatesSystem.hpp"
#include "ZipperIterator.hpp"

namespace ecs::systems {
    void EnnemiesMilepatesSystem::operator()(Registry &r, std::shared_ptr<IContext> ctx)
    {
        auto &positions = r.get_components<ecs::component::Position>();
        auto &animations = r.get_components<ecs::component::Animations>();
        auto &controllable = r.get_components<ecs::component::Controllable>();

        if (countMilepates(r) == 0) {
            createMilepates(r, ctx);
            return;
        }

        int i = 0;

        for (auto &&[pos, anim, control] : custom_zip(positions, animations, controllable)) {
            if (!pos || !anim || !control || anim->_object == ecs::component::InDestroy ||
                anim->_type != ecs::component::Type::Milespates) {
                continue;
            }

            if (i == 0) {

                if (pos->_y > HEIGHT_MAX && !pos->_changeDirection) {
                    pos->_changeDirection = true;
                    pos->_y = HEIGHT_MAX - 1;
                } else if (pos->_y < HEIGHT_MIN && pos->_changeDirection) {
                    pos->_changeDirection = false;
                    pos->_y = HEIGHT_MIN + 1;
                }

                if (anim->_clock.getSeconds() > MILESPATES_SPEED_ANIMATION) {
                    pos->_x -= control->_speed;

                    if (pos->_changeDirection) {
                        pos->_y -= control->_speed;
                    } else {
                        pos->_y += control->_speed;
                    }

                    positionHistory.push_front({pos->_x, pos->_y});

                    if (positionHistory.size() > NB_ENNEMIES * 10) {
                        positionHistory.pop_back();
                    }

                    anim->_clock.restart();
                }
                i += 1;
            } else {
                if (!positionHistory.empty() && anim->_clock.getSeconds() > MILESPATES_SPEED_ANIMATION) {
                    if (i * 10 < positionHistory.size()) {
                        auto [followX, followY] = positionHistory[i * 10];
                        pos->_x = followX + i * MARGIN_X;
                        pos->_y = followY;
                        anim->_clock.restart();
                    }
                }
                i += 1;
            }
        }
    }

    void EnnemiesMilepatesSystem::createMilepates(Registry &r, std::shared_ptr<IContext> &ctx)
    {
        auto rp = std::make_shared<Registry>(r);
        auto factory = ecs::ComponentFactory(rp, ecs::ComponentFactory::Mode::Client);
        std::vector<Entity> milespates;
        int lastX = 1944;
        int lastY = 80;

        for (std::size_t i = 0; i < NB_ENNEMIES; ++i) {
            milespates.push_back(factory.createEntity("config/milepates.json"));
            ctx->createMilespates(milespates[i].getId());
        }

        auto &positions = r.get_components<ecs::component::Position>();
        // auto &drawables = r.get_components<ecs::component::Drawable>();
        // auto &controllable = r.get_components<ecs::component::Controllable>();
        // auto &sprites = r.get_components<ecs::component::Sprite>();
        // auto &animations = r.get_components<ecs::component::Animations>();
        // auto &sizes = r.get_components<ecs::component::Size>();
        // auto &destroyable = r.get_components<ecs::component::Destroyable>();
        // auto &life = r.get_components<ecs::component::Life>();

        for (const auto &i : milespates) {
            positions[i.getId()] = ecs::component::Position{lastX -= 20, lastY += 60, false};
            //     drawables[i.getId()] = ecs::component::Drawable{true};
            //     controllable[i.getId()] = ecs::component::Controllable{false, MILESPATES_SPEED};
            //     sprites[i.getId()] = ecs::component::Sprite{MILESPATES_SPRITE};
            //     life[i.getId()] = ecs::component::Life{1};
            //     animations[i.getId()] = ecs::component::Animations{
            //         ecs::Clock(), 30, 30, 0, 0, 0, ecs::component::Object::Ennemies, ecs::component::Type::Milespates
            //     };
            //     sizes[i.getId()] = ecs::component::Size{2.8, 2.8};
            //     destroyable[i.getId()] = ecs::component::Destroyable{false};
        }
    }

    int EnnemiesMilepatesSystem::countMilepates(Registry &r)
    {
        auto &animations = r.get_components<ecs::component::Animations>();
        int nbMilespates = 0;

        for (auto &&[anim] : ecs::custom_zip(animations)) {
            if (!anim) {
                continue;
            }

            if (anim->_type == ecs::component::Type::Milespates) {
                nbMilespates += 1;
            }
        }

        return nbMilespates;
    }
} // namespace ecs::systems
