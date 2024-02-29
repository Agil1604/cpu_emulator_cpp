#include <iostream>

namespace my_stack
{
    template <typename T>
    class stack
    {
    private:
    public:
        void push(T elem);
        void pop();
        T top();
    };
    template <typename T>
    inline void stack<T>::push(T elem)
    {
    }

    template <typename T>
    inline void stack<T>::pop()
    {
    }

    template <typename T>
    inline T stack<T>::top()
    {
        return T();
    }
}
