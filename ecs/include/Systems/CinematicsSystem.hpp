/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CinematicsSystem
*/

#ifndef CINEMATICSSYSTEM_HPP_
#define CINEMATICSSYSTEM_HPP_

#define CINEMATICS_SYSTEM "Cinematics system"

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class CinematicsSystem : public ISystems {
          public:
            CinematicsSystem() = default;

            std::string getName() const override {
                return CINEMATICS_SYSTEM;
            }

            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !CINEMATICSSYSTEM_HPP_ */
