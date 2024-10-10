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
    /// @brief IContext class is an Interface of context. The GUI must have a class for window handling... that heritate of the IContext
    class IContext {
      public:
        /// @brief virtual default destructor
        virtual ~IContext() = default;

        /// @brief run method to run the GUI
        /// @return it return an int, 0 in success, and error is what you prefered
        virtual int run() = 0;
    };
} // namespace ecs

#endif /* !CONTEXT_HPP_ */
