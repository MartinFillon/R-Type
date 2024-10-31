/*
** EPITECH PROJECT, 2024
** r type proj
** File description:
** EnnemiesMilepatesSystem
*/

#include "Systems/EnnemiesMilepatesSystem.hpp"
#include <iostream>
#include <memory>
#include "ComponentFactory.hpp"
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Position.hpp"
#include "IContext.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

namespace ecs::systems {
    void EnnemiesMilepatesSystem::operator()(
        std::shared_ptr<Registry> &r,
        std::shared_ptr<IContext> ctx,
        ComponentFactory &factory
    )
    {
        auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();
        auto &positions = r->register_if_not_exist<ecs::component::Position>();
        auto &animations = r->register_if_not_exist<ecs::component::Animations>();
        auto &controllables = r->register_if_not_exist<ecs::component::Controllable>();
        auto &destroyables = r->register_if_not_exist<ecs::component::Destroyable>();

        if (countMilepates(r) == 0) {
            createMilepates(r, ctx, factory);
            return;
        }

        int i = 0;

        for (auto &&[atr, pos, anim, control, destroyable] :
             custom_zip(attributes, positions, animations, controllables, destroyables)) {
            if (!atr || !pos || !anim || !control ||
                destroyable->_state != ecs::component::Destroyable::DestroyState::ALIVE ||
                atr->_secondary_type != ecs::component::Attributes::SecondaryType::Milespates) {
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

    void EnnemiesMilepatesSystem::createMilepates(
        std::shared_ptr<Registry> &r,
        std::shared_ptr<IContext> &ctx,
        ComponentFactory &factory
    )
    {
        std::vector<Entity> milespates;
        int lastX = 1944;
        int lastY = 80;

        for (std::size_t i = 0; i < NB_ENNEMIES; ++i) {
            try {
                milespates.push_back(factory.createEntity(r, CONFIG_MILEPATES));
                r->_entities.addEntity(milespates[i].getId());
                ctx->createMilespates(milespates[i].getId());
            } catch (const ecs::ComponentFactory::ComponentFactoryException &error) {
                std::cerr << error.what() << std::endl;
            }
        }

        auto &positions = r->register_if_not_exist<ecs::component::Position>();

        for (const auto &i : milespates) {
            positions[i.getId()] = ecs::component::Position{lastX -= 20, lastY += 60, false};
        }
    }

    int EnnemiesMilepatesSystem::countMilepates(std::shared_ptr<Registry> &r)
    {
        auto &attributes = r->register_if_not_exist<ecs::component::Attributes>();
        int nbMilespates = 0;

        for (auto &&[atr] : ecs::custom_zip(attributes)) {
            if (!atr) {
                continue;
            }

            if (atr->_secondary_type == ecs::component::Attributes::SecondaryType::Milespates) {
                nbMilespates += 1;
            }
        }

        return nbMilespates;
    }
} // namespace ecs::systems
