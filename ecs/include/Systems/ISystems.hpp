/*
** EPITECH PROJECT, 2024
** RType
** File description:
** ISystems
*/

#ifndef ISYSTEMS_HPP_
    #define ISYSTEMS_HPP_

#include "Registery.hpp"

namespace ecs {
    namespace systems {
        class ISystems {
          public:
            virtual void operator()(Registry &) = 0;
        };
    };
};

#endif /* ISYSTEMS_HPP_ */
