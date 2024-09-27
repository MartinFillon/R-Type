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
class Entity {
  public:
    Entity(std::size_t id) : _id(id) {}

    std::size_t getId() const
    {
        return _id;
    }

    bool operator==(const Entity &other) const
    {
        return _id == other._id;
    }

  private:
    std::size_t _id;
};
} // namespace ecs

#endif /* !ENTITY_HPP_ */
