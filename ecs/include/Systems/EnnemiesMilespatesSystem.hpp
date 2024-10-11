/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnnemiesMilespatesSystem
*/

#ifndef ENNEMIESMILESPATESSYSTEM_HPP_
#define ENNEMIESMILESPATESSYSTEM_HPP_

#define NB_ENNEMIES 4

#define MILESPATES_SPEED 3.5
#define MILESPATES_SPEED_ANIMATION 0.01
#define MILESPATES_SPRITE "r-typesheet8.gif"

#define HEIGHT_MIN 0
#define HEIGHT_MAX 400

#define MARGIN_X 40
#define FOLLOW_DISTANCE 70

#include <deque>
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class EnnemiesMilespatesSystem : public ISystems {
          public:
            void operator()(Registry &, std::shared_ptr<IContext> ctx) override;

            void createMilespates(Registry &r);
            int countMilespates(Registry &r);
            std::deque<std::pair<int, int>> positionHistory;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !ENNEMIESMILESPATESSYSTEM_HPP_ */
