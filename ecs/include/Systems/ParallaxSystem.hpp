/*
** EPITECH PROJECT, 2024
** RType
** File description:
** ParalaxSystem
*/

#ifndef PARALAXSYSTEM_HPP_
#define PARALAXSYSTEM_HPP_

#include "Clock.hpp"

#define BACKGROUND_SPEED 0.01
#define BACKGROUND_TICK 3
#define SCREEN_WIDTH 1920

#include "ISystems.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

namespace ecs {
    namespace systems {
        class ParalaxSystem : public ISystems {
          public:
            void operator()(Registry &r);

          private:
            Clock _clock;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !PARALAXSYSTEM_HPP_ */
