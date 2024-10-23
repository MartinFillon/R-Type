/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PunchSystem
*/

#ifndef PUNCHSYSTEM_HPP_
#define PUNCHSYSTEM_HPP_

#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class PunchSystem : public ISystems {
          public:
            void operator()(Registry &r, std::shared_ptr<IContext> ctx) override;

        };
    }; // namespace systems
}; // namespace ecs

#endif /* !PUNCHSYSTEM_HPP_ */
