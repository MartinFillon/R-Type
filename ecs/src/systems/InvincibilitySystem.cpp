/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InvincibilitySystem
*/

#include "Systems/InvincibilitySystem.hpp"
#include "Components/Destroyable.hpp"
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
            auto &destroyable = r->register_if_not_exist<component::Destroyable>();

            for (std::size_t i = 0; i < invincibility.size(); ++i) {
                if (!invincibility[i].has_value()) {
                    continue;
                }
                if (!invincibility[i]->_invincible) {
                    continue;
                }
                if (!destroyable[i] || !destroyable[i]->_state != ecs::component::Destroyable::DestroyState::ALIVE) {
                    invincibility[i]->_invincible = false;
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
