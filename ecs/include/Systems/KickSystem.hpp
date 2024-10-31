/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** KickSystem
*/

#ifndef KICKSYSTEM_HPP_
#define KICKSYSTEM_HPP_

#define KICK_ANIMATION 0.09
#define END_OF_KICK_ANIMATION 280
#define WIDTH_KICK_PADDING 5
#define WIDTH_ADD_PADDING 2

#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class KickSystem : public ISystems {
          public:
            KickSystem() = default;
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !KICKSYSTEM_HPP_ */
