#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <memory>
#include <initializer_list>


template <class T>
class Dynamic_array
{
private:
    size_t m_array_size = 0;
    std::unique_ptr<T[]> m_data_array;

    inline void check_index(size_t index) const
    {
        if (index >= m_array_size) {
            throw std::out_of_range("Out of range. Size of the dynamic array is equal to " + std::to_string(m_array_size));
        }
    }

public:

    Dynamic_array() = default;

    Dynamic_array(size_t size) :
        m_array_size{ size },
        m_data_array{ new T[m_array_size] }
    {}

    Dynamic_array(size_t size, const T& value) :
        m_array_size{ size },
        m_data_array{ new T[m_array_size] }
    {
        std::fill(begin(), end(), value);
    }

    Dynamic_array(size_t size, T&& value) :
        m_array_size{ size },
        m_data_array{ new T[m_array_size] }
    {
        std::fill(begin(), end(), value);
    }

    Dynamic_array(const Dynamic_array& other) :
        m_array_size{ other.m_array_size },
        m_data_array{ new T[m_array_size] }
    {
        std::copy(other.cbegin(), other.cend(), begin());
    }

    Dynamic_array(Dynamic_array&& other) :
        m_array_size{ other.m_array_size },
        m_data_array{ std::move(other.m_data_array) }
    {
        other.m_array_size = 0;
    }
    //
    Dynamic_array(std::initializer_list<T> init_list) :
        m_array_size{ init_list.size() },
        m_data_array{ new T[m_array_size] }
    {
        std::copy(init_list.begin(), init_list.end(), begin());
    }

    ~Dynamic_array() = default;

    T& operator[](size_t index)
    {
        check_index(index);
        return m_data_array[index];
    }

    const T& operator[](size_t index) const
    {
        check_index(index);
        return m_data_array[index];
    }

    size_t size() const
    {
        return m_array_size;
    }

    Dynamic_array& operator=(const Dynamic_array& other)
    {
        if (m_array_size != other.m_array_size) {
            m_array_size = other.m_array_size;
            m_data_array.reset(new T[m_array_size]);
        }

        std::copy(other.cbegin(), other.cend(), begin());
        return *this;
    }

    Dynamic_array& operator=(Dynamic_array&& other)
    {
        m_array_size = other.m_array_size;
        m_data_array = std::move(other.m_data_array);
        other.m_array_size = 0;
        return *this;
    }

    Dynamic_array& operator=(std::initializer_list<T> init_list)
    {
        if (m_array_size != init_list.size()) {
            m_array_size = init_list.size();
            m_data_array.reset(new T[m_array_size]);
        }

        std::copy(init_list.begin(), init_list.end(), begin());
        return *this;
    }

    bool operator==(const Dynamic_array& other) const
    {
        return std::equal(cbegin(), cend(), other.cbegin());
    }

    bool operator!=(const Dynamic_array& other) const
    {
        return !(operator==(other));
    }

    void print() const
    {
        for (size_t i = 0; i < m_array_size; i++)
        {
            std::cout << m_data_array[i] << " ";
        }
        std::cout << std::endl;
    };

    // std::string to_string() const {

    // };


    //Iterators
    class Iterator {
        T* m_it;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator(T* iter) : m_it{ iter }
        {}

        bool operator!=(const Iterator& other)
        {
            return m_it != other.m_it;
        }

        bool operator==(const Iterator& other)
        {
            return m_it == other.m_it;
        }

        Iterator& operator++()
        {
            m_it++;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator result{ m_it++ };
            return result;
        }

        Iterator& operator+(int number)
        {
            m_it += number;
            return *this;
        }

        Iterator& operator+=(int number)
        {
            m_it += number;
            return *this;
        }

        Iterator& operator--()
        {
            m_it--;
            return *this;
        }

        Iterator operator--(int) {
            Iterator result{ m_it-- };
            return result;
        }

        Iterator& operator-(int number)
        {
            m_it -= number;
            return *this;
        }

        Iterator& operator-=(int number)
        {
            m_it -= number;
            return *this;
        }

        bool operator>(const Iterator& other)
        {
            return (m_it) > (other.m_it);
        }

        bool operator<(const Iterator& other)
        {
            return (m_it) < (other.m_it);
        }

        T& operator*()
        {
            return *m_it;
        }
        T* operator->()
        {
            return m_it;
        }
    };

    class Const_iterator {
        const T* m_it;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::bidirectional_iterator_tag;

        Const_iterator(const T* iter) : m_it{ iter }
        {}

        bool operator!=(const Const_iterator& other)
        {
            return m_it != other.m_it;
        }

        bool operator==(const Const_iterator& other)
        {
            return m_it == other.m_it;
        }

        Const_iterator& operator++()
        {
            m_it++;
            return *this;
        }

        Const_iterator operator++(int)
        {
            Iterator result{ m_it++ };
            return result;
        }

        Const_iterator& operator+(int number)
        {
            m_it += number;
            return *this;
        }

        Const_iterator& operator+=(int number)
        {
            m_it += number;
            return *this;
        }

        Const_iterator& operator--()
        {
            m_it--;
            return *this;
        }

        Const_iterator operator--(int) {
            Iterator result{ m_it-- };
            return result;
        }

        Const_iterator& operator-(int number)
        {
            m_it -= number;
            return *this;
        }

        Const_iterator& operator-=(int number)
        {
            m_it -= number;
            return *this;
        }

        bool operator>(const Const_iterator& other)
        {
            return (m_it) > (other.m_it);
        }

        bool operator<(const Const_iterator& other)
        {
            return (m_it) < (other.m_it);
        }

        const T& operator*()
        {
            return *m_it;
        }
        const T* operator->()
        {
            return m_it;
        }
    };

    Dynamic_array<T>::Iterator begin()
    {
        return Iterator(m_data_array.get());
    }

    Dynamic_array<T>::Iterator end()
    {
        return Iterator(m_data_array.get() + m_array_size);
    }

    Dynamic_array<T>::Const_iterator cbegin() const
    {
        return Const_iterator(m_data_array.get());
    }

    Dynamic_array<T>::Const_iterator cend() const
    {
        return Const_iterator(m_data_array.get() + m_array_size);
    }

    //TODO REVERSE ITERATOR - with Iterator inside
};

