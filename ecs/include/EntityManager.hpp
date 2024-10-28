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
#include "Defs.hpp"
#include "Entity.hpp"

namespace ecs {
    class EntityManager {
      public:
        EntityManager() = default;

        EntityManager(const std::size_t &id)
        {
            _entities.push_back(id);
        }

        EntityManager(const Entity &id)
        {
            _entities.push_back(id);
        }

        class EntityManagerError : std::exception {
          public:
            EntityManagerError(std::string message) : _message(message) {}

            ~EntityManagerError() = default;

            const char *what() const noexcept
            {
                return _message.c_str();
            }

          private:
            std::string _message;
        };

        void addEntity(const Entity &entity)
        {
            _entities.push_back(entity);
        }

        Entity operator[](const std::size_t &idx)
        {
            if (idx > _entities.size()) {
                throw EntityManagerError(ENTITY_MANAGER_ERROR_OUT_OF_RANGE);
                return Entity(0);
            }
            return _entities[idx];
        }

        void erase(const std::size_t &id)
        {
            for (std::size_t i = 0; i < _entities.size(); ++i) {
                if (_entities[i].getId() == id) {
                    _entities.erase(_entities.begin(), _entities.begin() + i);
                    continue;
                }
            }
        }

        std::size_t size() const
        {
            return _entities.size();
        }

        Entity lastEntity() const
        {
            return _entities[_entities.size() - 1];
        }

      private:
        std::vector<Entity> _entities;
    };
}; // namespace ecs

#endif /* !ENTITYMANAGER_HPP_ */
