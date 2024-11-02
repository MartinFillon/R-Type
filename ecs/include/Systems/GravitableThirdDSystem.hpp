/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GravitableThirdDSystem
*/

#ifndef GRAVITABLETHIRDDSYSTEM_HPP_
#define GRAVITABLETHIRDDSYSTEM_HPP_

#define MAX_Y 8
#define INITIAL_Y 0

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class GravitableThirdDSystem : public ISystems {
          public:
            GravitableThirdDSystem() = default;
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

          private:
            int findInitialY(std::shared_ptr<Registry> &r);
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !GRAVITABLETHIRDDSYSTEM_HPP_ */
