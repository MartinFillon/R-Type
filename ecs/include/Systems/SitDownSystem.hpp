/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SitDownSystem
*/

#ifndef SITDOWNSYSTEM_HPP_
#define SITDOWNSYSTEM_HPP_
#include "ISystems.hpp"

namespace ecs {
    namespace systems {
        class SitDownSystem : public ISystems {
          public:
            void operator()(Registry &r, std::shared_ptr<IContext> ctx) override;

        };
    }; // namespace systems
}; // namespace ecs

#endif /* !SITDOWNSYSTEM_HPP_ */
