/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionsSystem
*/

#ifndef COLLISIONSSYSTEM_HPP_
#define COLLISIONSSYSTEM_HPP_

#define WIDTH_MAX_LIMIT 2700
#define HEIGHT_MAX_LIMIT 2500

#define WIDTH_MIN_LIMIT -300
#define HEIGHT_MIN_LIMIT -300

#include "Registry.hpp"
#include "Systems/ISystems.hpp"

namespace ecs {
    namespace systems {
        class CollisionsSystem : public ISystems {
          public:
            void operator()(Registry &, std::shared_ptr<IContext> ctx) override;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* COLLISIONSSYSTEM_HPP_ */
