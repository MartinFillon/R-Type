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
    /// @brief EntityManager is a class for handling all Entity
    class EntityManager {
      public:
        /// @brief Default Constructor for entityManager
        EntityManager() = default;

        /// @brief Constructor for push_back a first id in the EntityManager
        /// @param id is the id of the first entity that will be push back
        EntityManager(const std::size_t &id)
        {
            _entities.push_back(Entity(id));
        }

        /// @brief Constructor for push_back a first Entity in the EntityManager
        /// @param id is the Entity that will be the first in the EntityManager
        EntityManager(const Entity &id)
        {
            _entities.push_back(id);
        }

        /// @brief EntityManager Error is here to handle the error of the EntityManager
        class EntityManagerError : std::exception {
          public:
            /// @brief EntityManagerError constructor take a string in parrameter and store it
            /// @param message 
            EntityManagerError(std::string message) : _message(message) {}

            ~EntityManagerError() = default;

            /// @brief What method for a catch error
            /// @return in const char *the message of the error
            const char *what() const noexcept
            {
                return _message.c_str();
            }

          private:
            /// @brief Error message that have been set in the constructor
            std::string _message;
        };

        /// @brief addEntity is a method that add an entity to the Entity Manager
        /// @param entity is the entity we want to add, if you have an std::size_t and not an Entity just call the Entity constructor like: "addEntity(Entity(std::size_t id))"
        void addEntity(const Entity &entity)
        {
            _entities.push_back(entity);
        }

        /// @brief operator[] method is to take an index of the EntityManager, to target an index, if it is superior it's throw an error
        /// @param idx is the index we want in the entityManager
        /// @return the Entity targeted
        Entity operator[](const std::size_t &idx)
        {
            if (idx > _entities.size()) {
                throw EntityManagerError(ENTITY_MANAGER_ERROR_OUT_OF_RANGE);
                return Entity(0);
            }
            return _entities[idx];
        }

        /// @brief erase method it to erase an id in the EntityManager
        /// @param id is the Id we want to erase
        void erase(const std::size_t &id)
        {
            for (std::size_t i = 0; i < _entities.size(); ++i) {
                if (_entities[i].getId() == id) {
                    _entities.erase(_entities.begin(), _entities.begin() + i);
                    continue;
                }
            }
        }

        /// @brief size method is to get the Size of the EntityManager
        /// @return the size as a std::size_t of the EntityManager
        std::size_t size() const
        {
            return _entities.size();
        }

        /// @brief lastEntity method is to get the last entity of the EntityManager
        /// @return the last entityof the EntityManager
        Entity lastEntity() const
        {
            return _entities[_entities.size() - 1];
        }

      private:
        /// @brief _entities is the vector of all Entity, it stored EntityClasses
        std::vector<Entity> _entities;
    };
}; // namespace ecs

#endif /* !ENTITYMANAGER_HPP_ */
