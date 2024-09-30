/*
** EPITECH PROJECT, 2024
** ZipperIterator
** File description:
** R type proj
*/

#ifndef ZIPPER_ITERATOR_HPP_
#define ZIPPER_ITERATOR_HPP_

#include <algorithm>
#include <cassert>
#include <iterator>
#include <optional>
#include <tuple>
#include <typeindex>
#include <utility>
#include <vector>
#include "SparseArray.hpp"

namespace ecs {

    template <typename... Arrays>
    class iterator {

      public:
        iterator(std::tuple<Arrays &...> arrays, size_t pos) : _arrays(arrays), _pos(pos) {}

        bool operator!=(const iterator &other) const
        {
            return _pos != other._pos;
        }

        void operator++()
        {
            ++_pos;
        }

        auto operator*()
        {
            return mul_args_helper(std::make_index_sequence<sizeof...(Arrays)>());
        }

      private:
        template <std::size_t... I>
        auto mul_args_helper(std::index_sequence<I...>)
        {
            return std::tuple<std::add_lvalue_reference_t<decltype(std::get<I>(_arrays)[_pos])>...>{std::get<I>(_arrays
            )[_pos]...};
        }

        std::tuple<Arrays &...> _arrays;
        size_t _pos;
    };

    template <typename... Arrays>
    class custom_zip {

      public:
        custom_zip(Arrays &...arrays) : _arrays(arrays...) {}

        auto begin()
        {
            return iterator<Arrays...>(_arrays, 0);
        }

        auto end()
        {
            return iterator<Arrays...>(_arrays, min_size());
        }

      private:
        std::size_t min_size() const
        {
            return std::apply([](const auto &...arrays) { return std::min({arrays.size()...}); }, _arrays);
        }

        std::tuple<Arrays &...> _arrays;
    };
} // namespace ecs

#endif /* !ZIPPERITERATOR_HPP_ */
