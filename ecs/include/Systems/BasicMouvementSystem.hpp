/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BasicMouvementSystem
*/

#ifndef BASICMOUVEMENTSYSTEM_HPP_
#define BASICMOUVEMENTSYSTEM_HPP_

#include "ISystems.hpp"
#include "nlohmann/json_fwd.hpp"

namespace ecs {
    namespace systems {
        class BasicMouvementSystem : public ISystems {
          public:
            BasicMouvementSystem(const nlohmann::json &config);
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !BASICMOUVEMENTSYSTEM_HPP_ */
