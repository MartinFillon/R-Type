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

    /// @brief Class to wrap all the utilities of the server side game rendering with the ECS.
    class Context : public ecs::IContext {

      public:
        /// @brief Generates a `Context` creating in the process an `ecs::IContext` from the given `network`.
        /// @param network a `std::shared_ptr<ecs::INetwork>` representing the network to link to the newly created
        /// context.
        Context(std::shared_ptr<ecs::INetwork> network);

        /// @brief Destructs the generated `Context` when out of scope.
        ~Context();

        /// @brief Broadcast a packet with `protocol::Operations::OBJECT_REMOVED` as optcode and the given `id` as
        /// argument.
        /// @param id an `int` representing the id of the entity which was destroyed.
        void destroyObject(int id) override final;

        /// @brief Broadcast a packet with `protocol::Operations::NEW_OBJECT` as optcode and the given `id` as
        /// arguments, specifying in the process that the created object is a `protocol::ObjectTypes::ENEMY`.
        /// @param id an `int` representing the id of the ennemy entity which was created.
        void createEnemy(int id) override final;

        /// @brief Broadcast a packet with `protocol::Operations::OBJECT_RECT` as optcode and the given `id` and `rect`
        /// informations as arguments.
        /// @param id an `int` representing the id of the animated entity.
        /// @param rect a `const ecs::component::Animations &` representing the reference to the reactangle animation
        /// sprite specifications.
        void animationObject(int id, const ecs::component::Animations &rect) override final;

        /// @brief Broadcast a packet with `protocol::Operations::OBJECT_POSITION` as optcode and the given `id`, `x`
        /// and `y` as arguments.
        /// @param id an `int` representing the id of the moved entity.
        /// @param x an `int` representing the horizontal position of the moved entity.
        /// @param y an `int` representing the vertical position of the moved entity.
        void moveObject(int id, int x, int y) override final;

        /// @brief Broadcast a packet with `protocol::Operations::NEW_OBJECT` as optcode and the given `id` and `type`
        /// as arguments.
        /// @param id an `int` representing the id of the projectile entity.
        /// @param type a `const rtype::protocol::ObjectTypes &` representing the reference of the type of object
        /// shooted.
        void createProjectile(int id, const rtype::protocol::ObjectTypes &type) override;

        /// @brief Broadcast a packet with `protocol::Operations::NEW_OBJECT` as optcode and the given `id` as argument,
        /// specifying in the process that the created object is a `protocol::ObjectTypes::MILESPATES`.
        /// @param id an `int` representing the if of the milespates entity which was created.
        void createMilespates(int id) override final;

        /// @brief Broadcast a packet with `protocol::Operations::NEW_OBJECT` as optcode and the given `id` as argument,
        /// specifying in the process that the created object is a `protocol::ObjectTypes::BOSS`.
        /// @param id an `int` representing the if of the boss entity which was created.
        void createBoss(int id) override final;

        /// @brief Broadcast a packet with `protocol::Operations::NEW_OBJECT` as optcode and the given `id` and `type`
        /// as arguments.
        /// @param id an `int` representing the id of the projectile entity.
        /// @param type a `const rtype::protocol::ObjectTypes &` representing the reference of the type of object
        /// shooted.
        void createBossProjectile(int id, const protocol::ObjectTypes &type) override final;

      protected:
      private:
    };
} // namespace rtype::server

#endif /* !CONTEXT_HPP_ */
