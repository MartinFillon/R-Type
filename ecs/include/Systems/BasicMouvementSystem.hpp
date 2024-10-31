/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BasicMouvementSystem
*/

#ifndef BASICMOUVEMENTSYSTEM_HPP_
#define BASICMOUVEMENTSYSTEM_HPP_

#define BASIC_MOUVEMENT_SYSTEM "Basic mouvement system"

#include <string>
#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class BasicMouvementSystem : public ISystems {
          public:
            BasicMouvementSystem() = default;

            std::string getName() const override {
                return BASIC_MOUVEMENT_SYSTEM;
            }

            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !BASICMOUVEMENTSYSTEM_HPP_ */
