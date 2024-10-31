/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ThirdDMouvementSystem
*/

#ifndef THIRDDMOUVEMENTSYSTEM_HPP_
#define THIRDDMOUVEMENTSYSTEM_HPP_

#define THIRD_D_MOUVEMENT_SYSTEM "3D Mouvement system"

#include "Components/Position3D.hpp"
#include "ISystems.hpp"
#include "nlohmann/json_fwd.hpp"

namespace ecs {
    namespace systems {
        class ThirdDMouvementSystem : public ISystems {
          public:
            ThirdDMouvementSystem() = default;
            ThirdDMouvementSystem(const nlohmann::json &config);

            std::string getName() const override {
                return THIRD_D_MOUVEMENT_SYSTEM;
            }

            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;
            bool checkCollision(std::shared_ptr<Registry> &r, ecs::component::Position3D &pos, ecs::component::Position3D previousPos);
        };
    }; // namespace systems
}; // namespace ecs


#endif /* !THIRDDMOUVEMENTSYSTEM_HPP_ */
