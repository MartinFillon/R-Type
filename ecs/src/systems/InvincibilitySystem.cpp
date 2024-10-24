/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InvincibilitySystem
*/

#include "Systems/InvincibilitySystem.hpp"
#include "Components/Invincibility.hpp"
#include "SystemsManager.hpp"

namespace ecs {
    namespace systems {
        void InvincibilitySystem::operator()(
            std::shared_ptr<Registry> &r,
            std::shared_ptr<IContext> ctx,
            ComponentFactory &factory
        )
        {
            auto &invincibility = r->register_if_not_exist<component::Invincibility>();

            for (std::size_t i = 0; i < invincibility.size(); ++i) {
                if (!invincibility[i].has_value()) {
                    continue;
                }
                if (!invincibility[i]->_invincible) {
                    continue;
                }
                if (invincibility[i]->_clock.getMiliSeconds() < invincibility[i]->_time_in_ms) {
                    continue;
                }

                invincibility[i]->_invincible = false;
            }
        }

    } // namespace systems
} // namespace ecs
