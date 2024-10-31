/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DestroySystem
*/

#ifndef DESTROYSYSTEM_HPP_
#define DESTROYSYSTEM_HPP_

#define DESTROY_SPRITE "assets/sprites/r-typesheet-explosion.gif"

#define DESTROY_ANIMATION 0.1
#define DESTROY_TICK 20 / 60

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class DestroySystem : public ISystems {
          public:
            DestroySystem() = default;
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

          private:
            Clock _clock;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !DESTROYSYSTEM_HPP_ */
