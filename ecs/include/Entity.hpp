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
    /// @brief Entity Classes for one entity, is an encapsulation of std::size_t
    class Entity {
      public:
        /// @brief Entity Constructor, it takes an id and set it to him
        /// @param id is the id that we want to set
        Entity(std::size_t id) : _id(id) {}

        /// @brief Copy constructor of Entity if we give an Entity and not a std::size_t
        /// @param e is the Entity we want to copy
        Entity(const Entity &e)
        {
            _id = e._id;
        }

        /// @brief getId method is a getter of the id of the Entity
        /// @return return his id that is a std::size_t
        std::size_t getId() const
        {
            return _id;
        }

        /// @brief operator= is to set an id to him
        /// @param id is a const reference of a std::size_t that we will stored
        /// @return it returns the id that we just stored
        std::size_t operator=(const std::size_t &id)
        {
            _id = id;
            return id;
        }

        /// @brief operator== is to make comparaison on Entity to check if the Entity is equal
        /// @param other is the other Entity we want to be compared
        /// @return a boolean to check if they are the same or not
        bool operator==(const Entity &other) const
        {
            return _id == other._id;
        }

      private:
        /// @brief _id is the id we stored as a std::size_t
        std::size_t _id;
    };
} // namespace ecs

#endif /* !ENTITY_HPP_ */
