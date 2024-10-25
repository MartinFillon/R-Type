/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnnemiesMilespatesSystem
*/

#ifndef ENNEMIESMILESPATESSYSTEM_HPP_
#define ENNEMIESMILESPATESSYSTEM_HPP_

#include "ComponentFactory.hpp"
#define NB_ENNEMIES 4

#define MILESPATES_SPEED 3.5
#define MILESPATES_SPEED_ANIMATION 0.01
#define MILESPATES_SPRITE "assets/sprites/r-typesheet8.gif"

#define HEIGHT_MIN 0
#define HEIGHT_MAX 400

#define MARGIN_X 40
#define FOLLOW_DISTANCE 70

#include <deque>
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class EnnemiesMilepatesSystem : public ISystems {
          public:
            EnnemiesMilepatesSystem() = default;
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

            void createMilepates(
                std::shared_ptr<Registry> &r,
                std::shared_ptr<IContext> &ctx,
                ComponentFactory &factory
            );
            int countMilepates(std::shared_ptr<Registry> &r);
            std::deque<std::pair<int, int>> positionHistory;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !ENNEMIESMILESPATESSYSTEM_HPP_ */
