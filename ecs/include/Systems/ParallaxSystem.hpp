/*
** EPITECH PROJECT, 2024
** RType
** File description:
** ParalaxSystem
*/

#ifndef PARALAXSYSTEM_HPP_
#define PARALAXSYSTEM_HPP_

#define BACKGROUND_SPEED 0.01
#define BACKGROUND_TICK 3
#define SCREEN_WIDTH 1920
#define PARALAX_SYSTEM_NAME "Paralax System"

#include "Clock.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class ParalaxSystem : public ISystems {
          public:
            ParalaxSystem() = default;

            std::string getName() const override {
                return PARALAX_SYSTEM_NAME;
            }

            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

          private:
            Clock _clock;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !PARALAXSYSTEM_HPP_ */
