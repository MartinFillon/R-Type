/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** KickSystem
*/

#ifndef KICKSYSTEM_HPP_
#define KICKSYSTEM_HPP_

#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class KickSystem : public ISystems {
          public:
            void operator()(Registry &r, std::shared_ptr<IContext> ctx) override;

        };
    }; // namespace systems
}; // namespace ecs

#endif /* !KICKSYSTEM_HPP_ */
