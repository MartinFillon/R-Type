/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Score
*/

#ifndef SCORE_HPP_
#define SCORE_HPP_

#include <string>

namespace ecs {
    namespace component {
        struct Score {
            double _score;
            std::string _name = "Score";
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SCORE_HPP_ */
