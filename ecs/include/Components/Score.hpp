/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Score
*/

#ifndef SCORE_HPP_
#define SCORE_HPP_

namespace ecs {
    namespace component {
        /// @brief Score component, store the score as a double to know the score of each entity
        struct Score {
            double _score;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SCORE_HPP_ */
