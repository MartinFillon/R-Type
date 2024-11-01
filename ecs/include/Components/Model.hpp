/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <sstream>
#include <string>
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Model : public IComponent {
            Model(std::string pathToModel): _pathToModel(pathToModel) {}
            Model() = default;
            std::string _pathToModel;
            std::string _name = "Model";
            std::string getName() const {
                return _name;
            }
            std::string getInfo() const {
                std::ostringstream stream;

                stream << _pathToModel;

                return stream.str();
            }
        };
    }; // namespace component
}; // namespace ecs


#endif /* !MODEL_HPP_ */
