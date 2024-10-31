/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionsSystem
*/

#ifndef COLLISIONSSYSTEM_HPP_
#define COLLISIONSSYSTEM_HPP_

#define COLLISIONS_SYSTEM "Collisions system"

#include <memory>

#include "IContext.hpp"
#include "Registry.hpp"
#include "Systems/ISystems.hpp"

namespace ecs {
    namespace systems {
        class CollisionsSystem : public ISystems {
          public:
            CollisionsSystem() = default;
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

            std::string getName() const override {
                return COLLISIONS_SYSTEM;
            }

          private:
            int _width_max_limit = WIDTH_MAX_LIMIT;
            int _height_max_limit = HEIGHT_MAX_LIMIT;
            int _width_min_limit = WIDTH_MIN_LIMIT;
            int _height_min_limit = HEIGHT_MIN_LIMIT;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* COLLISIONSSYSTEM_HPP_ */
