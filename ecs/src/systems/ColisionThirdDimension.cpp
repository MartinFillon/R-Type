/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ColisionThirdDimension
*/

#include "Systems/ColisionThirdDimension.hpp"
#include "Components/Attributes.hpp"
#include "Components/Position3D.hpp"

void ecs::systems::ColisionThirdDimension::operator()(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<IContext> ctx,
    ComponentFactory &factory
)
{
    auto &attributes = r->register_if_not_exist<component::Attributes>();
    auto &position3D = r->register_if_not_exist<component::Position3D>();

    for (std::size_t i = 0; i < position3D.size(); ++i) {
        if (!attributes[i] || !position3D[i]) {
            continue;
        }   

        if (attributes[i]->_entity_type != component::Attributes::EntityType::Player) {
            continue;
        }   
        for (std::size_t j = 0; j < position3D.size(); ++j) {
            if (i == j || !attributes[j] || !position3D[j]) {
                continue;
            }   

            if (attributes[j]->_entity_type == component::Attributes::EntityType::Rectangle) {

                if (position3D[i]->_x == position3D[j]->_x &&
                    position3D[i]->_y == position3D[j]->_y &&
                    position3D[i]->_z == position3D[j]->_z) {
                    position3D[i]->_changeDirection = true;
                }
            }
        }
    }
}
