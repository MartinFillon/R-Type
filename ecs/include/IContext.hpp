/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Context
*/

#ifndef ICONTEXT_HPP_
#define ICONTEXT_HPP_

#include <memory>
#include "INetwork.hpp"

#define GAME_NAME "R-Type"

namespace ecs {
    class IContext {
      public:
        IContext() = default;

        IContext(std::shared_ptr<INetwork> network) : _network(network) {}

        virtual ~IContext() = default;

        std::shared_ptr<INetwork> _network = nullptr;

      protected:
    };
} // namespace ecs

#endif /* !ICONTEXT_HPP_ */
