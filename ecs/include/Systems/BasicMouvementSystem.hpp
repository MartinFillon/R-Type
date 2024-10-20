/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BasicMouvementSystem
*/

#ifndef BASICMOUVEMENTSYSTEM_HPP_
#define BASICMOUVEMENTSYSTEM_HPP_

#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class BasicMouvementSystem : public ISystems {
          public:
            void operator()(Registry &r, std::shared_ptr<IContext> ctx) override;

        };
    }; // namespace systems
}; // namespace ecs

#endif /* !BASICMOUVEMENTSYSTEM_HPP_ */
