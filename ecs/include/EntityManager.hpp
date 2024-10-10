/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <exception>
#include <string>
#include <vector>
#include "Entity.hpp"

#define ENTITY_MANAGER_ERROR_OUT_OF_RANGE "Out of range"

namespace ecs {
    /// @brief Class to wrap and manage all the entities of the ECS.
    class EntityManager {
      public:
        /// @brief Generates an empty `EntityManager`.
        EntityManager() = default;

        /// @brief Generates an `EntityManager` pushing in the process the given entity `id` into itself.
        /// @param id a `const std::size_t &` representing the reference of the first entity id to push to the entity
        /// manager.
        EntityManager(const std::size_t &id)
        {
            _entities.push_back(Entity(id));
        }

        /// @brief Generates an `EntityManager` pushing in the process the given entity into itself.
        /// @param id a `const Entity &` representing the reference of the first entity to push to the entity manager.
        EntityManager(const Entity &id)
        {
            _entities.push_back(id);
        }

        /// @brief Class that handles the exceptions that can be lead to by the entity manager.
        class EntityManagerError : std::exception {
          public:
            /// @brief Generates a `EntityManagerError` with the given `message` attached to it.
            /// @param message a `std::string` representing the exception message.
            EntityManagerError(std::string message) : _message(message) {}

            ~EntityManagerError() = default;

            /// @brief Method for a catch error.
            /// @return `const char *` representing the error's message.
            const char *what() const noexcept
            {
                return _message.c_str();
            }

          private:
            /// @brief The error's message.
            std::string _message;
        };

        /// @brief Adds the given entity to the entity manager.
        /// @param entity a `const Entity &` representing the reference of the entity to add to the manager.
        void addEntity(const Entity &entity)
        {
            _entities.push_back(entity);
        }

        /// @brief Get the entity at the given `idx`.
        /// @param idx a `const std::size_t &` representing the reference of the index to check.
        /// @return `Entity` representing the found entity.
        Entity operator[](const std::size_t &idx)
        {
            if (idx > _entities.size()) {
                throw EntityManagerError(ENTITY_MANAGER_ERROR_OUT_OF_RANGE);
                return Entity(0);
            }
            return _entities[idx];
        }

        /// @brief Erases the entity of id `id` in the entity manager.
        /// @param id a `const std::size_t &` representing the id of the entity to erase.
        void erase(const std::size_t &id)
        {
            for (std::size_t i = 0; i < _entities.size(); ++i) {
                if (_entities[i].getId() == id) {
                    _entities.erase(_entities.begin(), _entities.begin() + i);
                    continue;
                }
            }
        }

        /// @brief Get the amount of entities contained in the entity manager.
        /// @return `std::size_t` representing the amount of entities in the entity manager.
        std::size_t size() const
        {
            return _entities.size();
        }

        /// @brief Get the last entity of the stored entities in the entity manager.
        /// @return `Entity` representing the last entity of the stored entities in the entity manager
        Entity lastEntity() const
        {
            return _entities[_entities.size() - 1];
        }

      private:
        /// @brief The list of the entities managed by the entity manager.
        std::vector<Entity> _entities;
    };
}; // namespace ecs

#endif /* !ENTITYMANAGER_HPP_ */
