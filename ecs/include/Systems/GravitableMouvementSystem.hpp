/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GravitableMouvementSystem
*/

#ifndef GRAVITABLEMOUVEMENTSYSTEM_HPP_
#define GRAVITABLEMOUVEMENTSYSTEM_HPP_

#define INITIAL_Y 500
#define END_SPRITE_SHEET 400
#define GRAVITY_JUMP_PADDING 40
#define GRAVITY_DOWN_PADDING * 4
#define MAX_Y (INITIAL_Y - 300)

#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class GravitableMouvementSystem : public ISystems {
          public:
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory) override;

        };
    }; // namespace systems
}; // namespace ecs

#endif /* !GRAVITABLEMOUVEMENTSYSTEM_HPP_ */
