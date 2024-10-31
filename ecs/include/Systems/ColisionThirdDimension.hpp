/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ColisionThirdDimension
*/

#ifndef COLISIONTHIRDDIMENSION_HPP_
#define COLISIONTHIRDDIMENSION_HPP_

#define COLISION_THIRD_D_DIMENSION_SYSTEM "Colision 3D dimension system"

#include "ISystems.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class ColisionThirdDimension : public ISystems {
          public:
            ColisionThirdDimension() = default;
            void operator()(std::shared_ptr<Registry> &r, std::shared_ptr<IContext> ctx, ComponentFactory &factory)
                override;

            std::string getName() const override {
                return COLISION_THIRD_D_DIMENSION_SYSTEM;
            }

          private:
            void sendDestroyedObject(std::shared_ptr<IContext> &ctx, std::size_t i);
        };
    }; // namespace systems
}; // namespace ecs


#endif /* !COLISIONTHIRDDIMENSION_HPP_ */
