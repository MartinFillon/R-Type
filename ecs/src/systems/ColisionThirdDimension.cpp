/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ColisionThirdDimension
*/

#include <iostream>

#include "Systems/ColisionThirdDimension.hpp"
#include "Components/Attributes.hpp"
#include "Components/Position3D.hpp"
#include "Components/RectangleShape.hpp"
#include "Components/Planes.hpp"

void ecs::systems::ColisionThirdDimension::operator()(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<IContext> ctx,
    ComponentFactory &factory
)
{
    auto &attributes = r->register_if_not_exist<component::Attributes>();
    auto &position3D = r->register_if_not_exist<component::Position3D>();
    auto &rectangles = r->get_components<component::RectangleShape>();
    auto &planes = r->get_components<component::Planes>();

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

            if (attributes[j]->_secondary_type == component::Attributes::SecondaryType::Killable) {
                
                int objWidth = 0;
                int objLength = 0;

                if (rectangles[j]) {
                    objWidth = rectangles[j]->_width;
                    objLength = rectangles[j]->_length;
                } else if (planes[j]) {
                    objWidth = planes[j]->_width;
                    objLength = planes[j]->_lenght;
                }

                if (position3D[i]->_x >= position3D[j]->_x - objWidth &&
                    position3D[i]->_x <= position3D[j]->_x + objWidth &&
                    position3D[i]->_z >= position3D[j]->_z - objLength &&
                    position3D[i]->_z <= position3D[j]->_z + objLength &&
                    position3D[i]->_y == position3D[j]->_y) {
                        position3D[i]->_x = -10;
                        position3D[i]->_y = 5;
                        position3D[i]->_z = 0;
                }
            }


            if (attributes[j]->_secondary_type == component::Attributes::SecondaryType::Finsih) {
                
                int objWidth = 0;
                int objLength = 0;

                if (rectangles[j]) {
                    objWidth = rectangles[j]->_width;
                    objLength = rectangles[j]->_length;
                } else if (planes[j]) {
                    objWidth = planes[j]->_width;
                    objLength = planes[j]->_lenght;
                }

                if (position3D[i]->_x >= position3D[j]->_x - objWidth &&
                    position3D[i]->_x <= position3D[j]->_x + objWidth &&
                    position3D[i]->_z >= position3D[j]->_z - objLength &&
                    position3D[i]->_z <= position3D[j]->_z + objLength) {
                        
                        std::cerr << "Game finished\n";
                }
            }

        }
    }
}
