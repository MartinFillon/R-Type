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
    class EntityManager {
      public:
        EntityManager() = default;

        EntityManager(const std::size_t &id)
        {
            _entitys.push_back(id);
        }

        EntityManager(const Entity &id)
        {
            _entitys.push_back(id);
        }

        class EntityManagerError : std::exception {
          public:
            EntityManagerError(std::string message) : _message(message) {}

            ~EntityManagerError() = default;
            const char *what() const noexcept;

          private:
            std::string _message;
        };

        void addEntity(const Entity &entity)
        {
            _entitys.push_back(entity);
        }

        Entity operator[](const std::size_t &idx)
        {
            if (idx > _entitys.size()) {
                throw EntityManagerError(ENTITY_MANAGER_ERROR_OUT_OF_RANGE);
            }
            return _entitys[idx];
        }

        std::size_t size() const
        {
            return _entitys.size();
        }

        Entity lastEntity() const
        {
            return _entitys[_entitys.size()];
        }

      private:
        std::vector<Entity> _entitys;
    };
}; // namespace ecs

#endif /* !ENTITYMANAGER_HPP_ */
