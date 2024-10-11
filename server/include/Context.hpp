/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Context
*/

#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include <memory>

#include "IContext.hpp"
#include "INetwork.hpp"

namespace rtype {
    class Context : ecs::IContext {
      public:
        Context(std::shared_ptr<ecs::INetwork> &network) : ecs::IContext(network) {};
        ~Context();

      protected:
      private:
    };
} // namespace rtype

#endif /* !CONTEXT_HPP_ */
