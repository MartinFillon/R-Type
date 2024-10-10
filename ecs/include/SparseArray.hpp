#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <optional>
#include <vector>

/// @brief namespaces ecs to encapsulate the ecs, systems, component
namespace ecs {
    /// @brief classes SparseArray is an encapsulation of a std::vector that taking a template "Component"
    /// @tparam Component is a template for all kind of Component, they are stored as a std::optional, they can be a nullopt
    template <typename Component>
    class SparseArray {
      public:
        /// @brief using value_type instead of std::optional<Component>
        using value_type = std::optional<Component>;
        /// @brief referece_type is a referece of value_type
        using reference_type = value_type &;
        /// @brief const_referece_type is a const referece of value_type
        using const_reference_type = value_type const &;
        /// @brief the container is std::vector of value_tupe aka std::vector of std::optionnal<Component>
        using container = std::vector<value_type>;
        /// @brief using a size_type instead of container::size_type of std::vector
        using size_type = typename container::size_type;
        /// @brief using iterator instead of container::iterator of std::vector
        using iterator = typename container::iterator;
        /// @brief using const_iterator instead of container::const_iterator of std::vector
        using const_iterator = typename container::const_iterator;

        SparseArray() {}

        /// @brief A copie constructor of a SparseArray to be an other Sparse Array
        /// @param other is a SparseArray, and take it's data
        SparseArray(SparseArray const &other) : _data(other._data) {}

        /// @brief A copie constructor of a SparseArray to be an other Sparse Array, we take it's rvalue
        /// @param other is a SparseArray, and take it's data
        SparseArray(SparseArray &&other) noexcept : _data(std::move(other._data)) {}

        /// @brief operator= to be an other SparseArray
        /// @param other is an const reference to an other SparseArray
        /// @return a referece to the new SparseArray
        SparseArray &operator=(SparseArray const &other)
        {
            if (this != &other) {
                _data = other._data;
            }
            return *this;
        }

        /// @brief operator= to be an other SparseArray
        /// @param other is an const reference to an other SparseArray, but only it's rvalue
        /// @return a referece to the new SparseArray
        SparseArray &operator=(SparseArray &&other) noexcept
        {
            if (this != &other) {
                _data = std::move(other._data);
            }
            return *this;
        }

        /// @brief set an nullopt on an index of the SparseArray when an entity is supposed to be destroy to opitmisate the memory
        /// @param idx is the index of the entity to "erase", it will be set to nullopt
        void erase(const std::size_t &idx)
        {
            if (idx < _data.size()) {
                _data[idx].reset();
            }
        }

        /// @return an iterator on the first index of the container
        iterator begin()
        {
            return _data.begin();
        }

        /// @return an const iterator on the first index of the container
        const_iterator begin() const
        {
            return _data.begin();
        }

        /// @return an const iterator on the first index of the container
        const_iterator cbegin() const
        {
            return _data.cbegin();
        }

        /// @return an iterator on the last index of the container
        iterator end()
        {
            return _data.end();
        }

        /// @return an const iterator on the last index of the container
        const_iterator end() const
        {
            return _data.end();
        }

        /// @return an const iterator on the last index of the container
        const_iterator cend() const
        {
            return _data.cend();
        }

        /// @brief the operator[] is to cible an index of the container, it's check if the index is superior of the container size
        /// @param idx is the index we want
        /// @return an reference of the index
        reference_type operator[](size_t idx)
        {
            if (idx >= _data.size()) {
                _data.resize(idx + 1);
            }
            return _data[idx];
        }

        /// @brief size() method is to know the size of the container
        /// @return an std::size_t of the container 
        std::size_t size() const
        {
            return _data.size();
        }

      private:
        /// @brief the container of the sparse array, it is the std::vector<std::optionnal<Component>>
        container _data;
    };
} // namespace ecs

#endif /* !SPARSEARRAY_HPP_ */
