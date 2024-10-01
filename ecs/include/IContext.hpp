/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Context
*/

#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#define GAME_NAME "R-Type"

namespace ecs {
    class IContext {
      public:
        virtual ~IContext() = default;

        virtual int run() = 0;
    };
} // namespace ecs

#endif /* !CONTEXT_HPP_ */
