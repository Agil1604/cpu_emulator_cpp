#pragma once
#include <iostream>

namespace my_stack
{
    /// @brief класс содержащий определение и поля стека
    /// @tparam T тип данных, который стек содержит
    template <typename T>
    class stack
    {
    private:
        T *ptr;
        size_t size;
        size_t n;
        static void swap(stack& left, stack& right) noexcept {
            std::swap(left.size, right.size);
            std::swap(left.n, right.n);
            std::swap(left.ptr, right.ptr);
        }
    public:
        void push(T elem);
        T pop();
        T& top();

        /// @brief дефолтный конструктор
        stack()
        {
            ptr = new T[100];
            size = 100;
            n = 0;
        }

        /// @brief конструктор копирования
        /// @param st корируемый объект
        explicit stack(const stack &st)
        {
            size = st.size;
            n = st.n;
            ptr = new T[size];
            for (size_t i = 0; i < n; ++i)
            {
                ptr[i] = st.ptr[i];
            }
        }

        /// @brief конструктор перемещения
        /// @param st rvalue reference на перемещаемый объект
        explicit stack(stack &&st) noexcept
        {
            size = st.size;
            n = st.n;
            ptr = st.ptr;
            st.ptr = nullptr;
        }

        /// @brief присваивание копированием
        /// @param other корируемый объект
        /// @return получившийся объект
        stack &operator=(const stack &other)
        {
            stack tmp(other);
            swap(*this, tmp);

            return *this;
        }

        /// @brief присваивание перемещением
        /// @param other rvalue reference на перемещаемый объект
        /// @return получившийся объект
        stack &operator=(stack &&other) noexcept
        {
            swap(*this, other);
            other.ptr = nullptr;

            return *this;
        }

        /// @brief деструктор
        ~stack()
        {
            delete[] ptr;
        }
    };

    /// @brief метод, который добавляет новый элемент в конец стека
    /// @tparam T тип данных, который стек содержит
    /// @param elem добавляемый элемент
    template <typename T>
    void stack<T>::push(T elem)
    {
        if (n < size)
        {
            ptr[n] = elem;
            n += 1;
        }
        else
        {
            T *tmp = new T[size + 100];
            for (size_t i = 0; i < size; ++i)
            {
                tmp[i] = ptr[i];
            }
            ptr[size] = elem;
            size += 100;
            n += 1;
        }
    }

    /// @brief метод, который удаляет верхний элемент стека
    /// @tparam T тип данных, который стек содержит
    template <typename T>
    T stack<T>::pop()
    {
        try
        {
            if (n == 0)
            {
                throw(0);
            }
        }
        catch(const std::exception& e)
        {
            std::cout << "stack is empty" << std::endl;
        }
        n -= 1;
        T tmp = ptr[n];
        return tmp;
    }

    /// @brief метод для просмотра верхнего элемента стека
    /// @tparam T тип данных, который стек содержит
    template <typename T>
    T& stack<T>::top()
    {
        try
        {
            if (n == 0)
            {
                throw(0);
            }
        }
        catch(const std::exception& e)
        {
            std::cout << "stack is empty" << std::endl;
        }
        return ptr[n - 1];
    }
}
