/*
** EPITECH PROJECT, 2024
** RType
** File description:
** ISystems
*/

#ifndef ISYSTEMS_HPP_
#define ISYSTEMS_HPP_

#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class ISystems {
          public:
            virtual void operator()(Registry &) = 0;
        };
    }; // namespace systems
};     // namespace ecs

#endif /* ISYSTEMS_HPP_ */
