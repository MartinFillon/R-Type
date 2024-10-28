/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GravitableThirdDSystem
*/

#ifndef GRAVITABLETHIRDDSYSTEM_HPP_
#define GRAVITABLETHIRDDSYSTEM_HPP_

#define MAX_Y 5
#define INITIAL_Y 0

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class GravitableThirdDSystem : public ISystems {
          public:
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !GRAVITABLETHIRDDSYSTEM_HPP_ */
