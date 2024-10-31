/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InvincibilitySystem
*/

#ifndef INVINCIBILITYSYSTEM_HPP_
#define INVINCIBILITYSYSTEM_HPP_

#define INVINCIBILITY_SYSTEM_NAME "Invincibility system"

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class InvincibilitySystem : public ISystems {
          public:
            InvincibilitySystem() = default;

            std::string getName() const override {
                return INVINCIBILITY_SYSTEM_NAME;
            }

            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !INVINCIBILITYSYSTEM_HPP_ */
