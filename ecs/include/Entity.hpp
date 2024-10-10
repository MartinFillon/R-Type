/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <cstddef>

namespace ecs {
    /// @brief Class to wrap all the utilities of the ECS's entities
    class Entity {
      public:
        /// @brief Generates an `Entity` from a given `id`.
        /// @param id a `std::size_t` representing the registry id to give to the newly created entity
        Entity(std::size_t id) : _id(id) {}

        /// @brief Generates an `Entity` from the reference of another entity.
        /// @param e a `const Entity &` representing the reference of the given entity to clone the registry id of.
        Entity(const Entity &e)
        {
            _id = e._id;
        }

        /// @brief Get the registry id of the entity.
        /// @return `std::size_t` representing the entity's registry id.
        std::size_t getId() const
        {
            return _id;
        }

        /// @brief Sets the id of the entity.
        /// @param id a `const std::size_t &` representing the reference of the registry id to set the entity to.
        /// @return `std::size_t` representing the newly stored registry id.
        std::size_t operator=(const std::size_t &id)
        {
            _id = id;
            return id;
        }

        /// @brief Checks if two entities registry ids are the same or not.
        /// @param other a `const Entity &` representing the reference of the other entity to compare the registry id
        /// with.
        /// @return `true` if the registry ids are corresponding, `false` otherwise.
        bool operator==(const Entity &other) const
        {
            return _id == other._id;
        }

      private:
        /// @brief The registry id of the entity.
        std::size_t _id;
    };
} // namespace ecs

#endif /* !ENTITY_HPP_ */
