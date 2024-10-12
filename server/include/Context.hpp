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
#include "Protocol.hpp"

namespace rtype::server {
    class Context : public ecs::IContext {
      public:
        Context(std::shared_ptr<ecs::INetwork> network);
        ~Context() {};

        void destroyObject(int id) override final;

        void createEnemy(int id) override final;

        void animationObject(int id, const ecs::component::Animations &rect) override final;

        void moveObject(int id, int x, int y) override final;

        void createProjectile(int id, const rtype::protocol::ObjectTypes &type) override;

      protected:
      private:
    };
} // namespace rtype::server

#endif /* !CONTEXT_HPP_ */
