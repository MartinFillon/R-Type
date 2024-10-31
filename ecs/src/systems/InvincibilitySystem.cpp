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
#include "ZipperIterator.hpp"

namespace ecs {
    namespace systems {
        void InvincibilitySystem::operator()(
            std::shared_ptr<Registry> &r,
            std::shared_ptr<IContext> ctx,
            ComponentFactory &factory
        )
        {
            auto &invincibilities = r->register_if_not_exist<component::Invincibility>();
            auto &destroyables = r->register_if_not_exist<component::Destroyable>();

            for (auto &&[invincibility, destroyable] : ecs::custom_zip(invincibilities, destroyables)) {
                if (!invincibility.has_value()) {
                    continue;
                }
                if (!invincibility->_invincible) {
                    continue;
                }
                if (!destroyable || !destroyable->_state != ecs::component::Destroyable::DestroyState::ALIVE) {
                    invincibility->_invincible = false;
                    continue;
                }
                if (invincibility->_clock.getMiliSeconds() < invincibility->_time_in_ms) {
                    continue;
                }

                invincibility->_invincible = false;
            }
        }

    } // namespace systems
} // namespace ecs
