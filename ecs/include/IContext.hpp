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
    /// @brief Interface representing the global runtime context.
    class IContext {
      public:
        /// @brief Virtual default constructor to overwrite.
        virtual ~IContext() = default;

        /// @brief Runs the context.
        /// @return `int` representing its status, 0 for ok, any other for error.
        virtual int run() = 0;
    };
} // namespace ecs

#endif /* !CONTEXT_HPP_ */
