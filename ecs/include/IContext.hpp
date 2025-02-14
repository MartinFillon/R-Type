/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Context
*/

#ifndef ICONTEXT_HPP_
#define ICONTEXT_HPP_

#include <memory>

#include "Components/Animations.hpp"
#include "INetwork.hpp"
#include "Protocol.hpp"

namespace ecs {
    class IContext {
      public:
        IContext() = default;

        IContext(std::shared_ptr<INetwork> network) : _network(network) {}

        virtual ~IContext() = default;

        virtual void destroyObject(int id) = 0;

        virtual void createEnemy(int id) = 0;

        virtual void animationObject(int id, const ecs::component::Animations &rect) = 0;

        virtual void moveObject(int id, int x, int y) = 0;

        virtual void createProjectile(int id, const rtype::protocol::ObjectTypes &type) = 0;

        virtual void createMilespates(int id) = 0;

        virtual void createBoss(int id) = 0;

        virtual void createBossProjectile(int id, const rtype::protocol::ObjectTypes &type) = 0;

        std::shared_ptr<INetwork> _network = nullptr;

      protected:
    };
} // namespace ecs

#endif /* !ICONTEXT_HPP_ */
