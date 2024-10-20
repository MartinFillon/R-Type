/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GravitableMouvementSystem
*/

#ifndef GRAVITABLEMOUVEMENTSYSTEM_HPP_
#define GRAVITABLEMOUVEMENTSYSTEM_HPP_
#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class GravitableMouvementSystem : public ISystems {
          public:
            void operator()(Registry &r, std::shared_ptr<IContext> ctx) override;

        };
    }; // namespace systems
}; // namespace ecs

#endif /* !GRAVITABLEMOUVEMENTSYSTEM_HPP_ */
