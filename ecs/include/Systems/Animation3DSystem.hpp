/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animation3DSystem
*/

#ifndef ANIMATION3DSYSTEM_HPP_
#define ANIMATION3DSYSTEM_HPP_

#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class Animation3DSystem : public ISystems {
          public:
            Animation3DSystem() = default;
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !ANIMATION3DSYSTEM_HPP_ */
