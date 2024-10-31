/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PunchSystem
*/

#ifndef PUNCHSYSTEM_HPP_
#define PUNCHSYSTEM_HPP_

#define END_OF_PUNCH_ANIMATION 130
#define SPEED_PUNCH_ANIMATION 0.09
#define WIDTH_PADDING 5

#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class PunchSystem : public ISystems {
          public:
            PunchSystem() = default;
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !PUNCHSYSTEM_HPP_ */
