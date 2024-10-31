/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Score
*/

#ifndef SCORE_HPP_
#define SCORE_HPP_

#include <string>
#include "Components/IComponent.hpp"

namespace ecs {
    namespace component {
        struct Score : public IComponent {
            Score(double score): _score(score) {}
            Score() = default;
            double _score;
            std::string _name = "Score";
            std::string getName() const {
                return _name;
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SCORE_HPP_ */
