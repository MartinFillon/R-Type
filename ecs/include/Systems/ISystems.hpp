/*
** EPITECH PROJECT, 2024
** RType
** File description:
** ISystems
*/

#ifndef ISYSTEMS_HPP_
#define ISYSTEMS_HPP_

#include <memory>
#include "ComponentFactory.hpp"
#include "IContext.hpp"
#include "Registry.hpp"

namespace ecs {
    namespace systems {
        class ISystems {
          public:
            virtual void operator()(
                std::shared_ptr<Registry> &r,
                std::shared_ptr<IContext> ctx,
                ComponentFactory &factory
            ) = 0;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* ISYSTEMS_HPP_ */
