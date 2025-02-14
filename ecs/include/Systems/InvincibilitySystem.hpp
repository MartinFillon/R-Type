/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InvincibilitySystem
*/

#ifndef INVINCIBILITYSYSTEM_HPP_
#define INVINCIBILITYSYSTEM_HPP_

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class InvincibilitySystem : public ISystems {
          public:
            InvincibilitySystem() = default;
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !INVINCIBILITYSYSTEM_HPP_ */
