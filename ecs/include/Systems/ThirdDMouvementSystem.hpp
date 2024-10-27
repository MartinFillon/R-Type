/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ThirdDMouvementSystem
*/

#ifndef THIRDDMOUVEMENTSYSTEM_HPP_
#define THIRDDMOUVEMENTSYSTEM_HPP_

#include "ISystems.hpp"
#include "nlohmann/json_fwd.hpp"

namespace ecs {
    namespace systems {
        class ThirdDMouvementSystem : public ISystems {
          public:
            ThirdDMouvementSystem(const nlohmann::json &config);
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
        };
    }; // namespace systems
}; // namespace ecs


#endif /* !THIRDDMOUVEMENTSYSTEM_HPP_ */
