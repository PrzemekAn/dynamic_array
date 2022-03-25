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
    size_t m_array_size = 0;
    std::unique_ptr<T[]> m_data_array;

    void check_index(size_t index) const
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
        Dynamic_array(size)
    {
        std::fill(begin(), end(), value);
    }

    Dynamic_array(size_t size, T&& value) :
        Dynamic_array(size)
    {
        std::fill(begin(), end(), value);
    }

    Dynamic_array(const Dynamic_array& other) :
        Dynamic_array(other.m_array_size)
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
        Dynamic_array(init_list.size())
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

    std::string to_string(std::string separator = ", ") const {
        std::stringstream str;
        str << '[';
        size_t last_element_index = m_array_size - 1;
        for (size_t i = 0; i < last_element_index; i++) {
            str << m_data_array[i];
            str << separator;
        }
        str << m_data_array[last_element_index] << ']';
        return str.str();
    };


    //Iterators
    class Iterator {
        T* m_ptr;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator(T* iter) : m_ptr{ iter }
        {}

        bool operator!=(const Iterator& other) const
        {
            return m_ptr != other.m_ptr;
        }

        bool operator==(const Iterator& other) const
        {
            return m_ptr == other.m_ptr;
        }

        Iterator& operator++()
        {
            m_ptr++;
            return *this;
        }

        Iterator operator++(int)
        {
            return m_ptr++;
        }

        Iterator operator+(int number) const
        {
            return m_ptr + number;
        }

        Iterator& operator--()
        {
            m_ptr--;
            return *this;
        }

        Iterator operator--(int) {
            return m_ptr--;
        }

        Iterator operator-(int number) const
        {
            return m_ptr - number;
        }

        Iterator& operator+=(int number)
        {
            m_ptr += number;
            return *this;
        }

        Iterator& operator-=(int number)
        {
            m_ptr -= number;
            return *this;
        }

        bool operator>(const Iterator& other) const
        {
            return m_ptr > other.m_ptr;
        }

        bool operator<(const Iterator& other) const
        {
            return m_ptr < other.m_ptr;
        }

        T& operator*()
        {
            return *m_ptr;
        }

        const T& operator*() const
        {
            return *m_ptr;
        }
        // T* operator->()
        // {
        //     return m_ptr;
        // }
    };

    class Const_iterator {
        const T* m_ptr;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::bidirectional_iterator_tag;

        Const_iterator(const T* iter) : m_ptr{ iter }
        {}

        Const_iterator(const Iterator& iter) :
            m_ptr{ &(*iter) }
        {}

        bool operator!=(const Const_iterator& other) const
        {
            return m_ptr != other.m_ptr;
        }

        bool operator==(const Const_iterator& other) const
        {
            return m_ptr == other.m_ptr;
        }

        Const_iterator& operator++()
        {
            m_ptr++;
            return *this;
        }

        Const_iterator operator++(int)
        {
            return m_ptr++;
        }

        Const_iterator operator+(int number) const
        {
            return m_ptr + number;
        }

        Const_iterator& operator+=(int number)
        {
            m_ptr += number;
            return *this;
        }

        Const_iterator& operator--()
        {
            m_ptr--;
            return *this;
        }

        Const_iterator operator--(int) {
            return m_ptr--;
        }

        Const_iterator operator-(int number) const
        {
            return m_ptr - number;
        }

        Const_iterator& operator-=(int number)
        {
            m_ptr -= number;
            return *this;
        }

        bool operator>(const Const_iterator& other) const
        {
            return m_ptr > other.m_ptr;
        }

        bool operator<(const Const_iterator& other) const
        {
            return m_ptr < other.m_ptr;
        }

        const T& operator*() const
        {
            return *m_ptr;
        }
        // const T* operator->()
        // {
        //     return m_ptr;
        // }
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

    class Reverse_iterator {
        Iterator m_forward_iterator;
    public:
        Reverse_iterator(Iterator it) :
            m_forward_iterator(it)
        {}

        bool operator!=(const Reverse_iterator& other) const
        {
            return m_forward_iterator != other.m_forward_iterator;
        }

        bool operator==(const Reverse_iterator& other) const
        {
            return m_forward_iterator == other.m_forward_iterator;
        }

        Reverse_iterator& operator++()
        {
            --m_forward_iterator;
            return *this;
        }

        Reverse_iterator operator++(int)
        {
            return m_forward_iterator--;
        }

        Reverse_iterator operator+(int number) const
        {
            return m_forward_iterator - number;
        }

        Reverse_iterator& operator+=(int number)
        {
            m_forward_iterator -= number;
            return *this;
        }

        Reverse_iterator& operator--()
        {
            m_forward_iterator++;
            return *this;
        }

        Reverse_iterator operator--(int) {
            return m_forward_iterator++;
        }

        Reverse_iterator operator-(int number) const
        {
            return m_forward_iterator + number;
        }

        Reverse_iterator& operator-=(int number)
        {
            m_forward_iterator += number;
            return *this;
        }

        bool operator>(const Reverse_iterator& other) const
        {
            return m_forward_iterator > other.m_forward_iterator;
        }

        bool operator<(const Reverse_iterator& other) const
        {
            return m_forward_iterator < other.m_forward_iterator;
        }

        T& operator*()
        {
            return *m_forward_iterator;
        }

        const T& operator*() const
        {
            return *m_forward_iterator;
        }

        // T* operator->()
        // {
        //     return m_forward_iterator.operator->();
        // }
    };

    class Const_reverse_iterator {
        Const_iterator m_forward_iterator;
    public:
        Const_reverse_iterator(Const_iterator it) :
            m_forward_iterator(it)
        {}

        Const_reverse_iterator(Reverse_iterator it) :
            m_forward_iterator{ &(*it) }
        {}

        bool operator!=(const Const_reverse_iterator& other) const
        {
            return m_forward_iterator != other.m_forward_iterator;
        }

        bool operator==(const Const_reverse_iterator& other) const
        {
            return m_forward_iterator == other.m_forward_iterator;
        }

        Const_reverse_iterator& operator++()
        {
            --m_forward_iterator;
            return *this;
        }

        Const_reverse_iterator operator++(int)
        {
            return m_forward_iterator--;
        }

        Const_reverse_iterator operator+(int number) const
        {
            return m_forward_iterator - number;
        }

        Const_reverse_iterator& operator+=(int number)
        {
            m_forward_iterator -= number;
            return *this;
        }

        Const_reverse_iterator& operator--()
        {
            ++m_forward_iterator;
            return *this;
        }

        Const_reverse_iterator operator--(int) {
            return m_forward_iterator++;
        }

        Const_reverse_iterator operator-(int number) const
        {
            return m_forward_iterator + number;
        }

        Const_reverse_iterator& operator-=(int number)
        {
            m_forward_iterator += number;
            return *this;
        }

        bool operator>(const Const_reverse_iterator& other) const
        {
            return m_forward_iterator > other.m_forward_iterator;
        }

        bool operator<(const Const_reverse_iterator& other) const
        {
            return m_forward_iterator < other.m_forward_iterator;
        }

        const T& operator*() const
        {
            return *m_forward_iterator;
        }

        // T* operator->()
        // {
        //     return m_forward_iterator.operator->();
        // }
    };

    Dynamic_array<T>::Reverse_iterator rbegin() {
        return Reverse_iterator(end() - 1);
    }

    Dynamic_array<T>::Reverse_iterator rend() {
        return Reverse_iterator(begin() - 1);
    }

    Dynamic_array<T>::Const_reverse_iterator crbegin() const
    {
        return Const_reverse_iterator(cend() - 1);
    }

    Dynamic_array<T>::Const_reverse_iterator crend() const
    {
        return Const_reverse_iterator(cbegin() - 1);
    }
};

