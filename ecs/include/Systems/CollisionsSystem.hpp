/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionsSystem
*/

#ifndef COLLISIONSSYSTEM_HPP_
#define COLLISIONSSYSTEM_HPP_

#include <memory>

#include "IContext.hpp"
#include "Registry.hpp"
#include "Systems/ISystems.hpp"

namespace ecs {
    namespace systems {
        class CollisionsSystem : public ISystems {
          public:
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

          private:
            void sendDestroyedObject(std::shared_ptr<IContext> &ctx, std::size_t i);
            int _width_max_limit;
            int _height_max_limit;
            int _width_min_limit;
            int _height_min_limit;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* COLLISIONSSYSTEM_HPP_ */
