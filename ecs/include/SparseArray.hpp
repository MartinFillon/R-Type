#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <optional>
#include <vector>

namespace ecs {
    template <typename Component>
    class SparseArray {
      public:
        using value_type = std::optional<Component>;
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container = std::vector<value_type>;
        using size_type = typename container::size_type;
        using iterator = typename container::iterator;
        using const_iterator = typename container::const_iterator;

        SparseArray() {}

        SparseArray(SparseArray const &other) : _data(other._data) {}

        SparseArray(SparseArray &&other) noexcept : _data(std::move(other._data)) {}

        SparseArray &operator=(SparseArray const &other)
        {
            if (this != &other) {
                _data = other._data;
            }
            return *this;
        }

        SparseArray &operator=(SparseArray &&other) noexcept
        {
            if (this != &other) {
                _data = std::move(other._data);
            }
            return *this;
        }

        void erase(const std::size_t &idx)
        {
            _data.erase(_data.begin(), _data.begin() + idx);
        }

        iterator begin()
        {
            return _data.begin();
        }

        const_iterator begin() const
        {
            return _data.begin();
        }

        const_iterator cbegin() const
        {
            return _data.cbegin();
        }

        iterator end()
        {
            return _data.end();
        }

        const_iterator end() const
        {
            return _data.end();
        }

        const_iterator cend() const
        {
            return _data.cend();
        }

        reference_type operator[](size_t idx)
        {
            if (idx >= _data.size()) {
                _data.resize(idx + 1);
            }
            return _data[idx];
        }

        std::size_t size() const
        {
            return _data.size();
        }

      private:
        container _data;
    };
} // namespace ecs

#endif /* !SPARSEARRAY_HPP_ */
