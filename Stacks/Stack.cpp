#ifndef STACK_CPP
#define STACK_CPP

#include "Stack.hpp"

template <typename T>
Stack<T>::Stack() {}

// TODO: Implement all other methods defined in Stack.hpp here

template <typename T>
Stack<T>::Stack(const std::vector<T> &items)
{

    for (const T &item : items)
    {
        push(item);
    }
}
template <typename T>
size_t Stack<T>::size() const
{
    return _llist.size();
}
template <typename T>
std::optional<T> Stack<T>::top() const
{
    if (_llist.size() < 1)
    {
        return std::nullopt;
    }
    return _llist.head()->value;
}

template <typename T>
void Stack<T>::push(T value)
{
    _llist.prepend(value);
}

template <typename T>
std::optional<T> Stack<T>::pop()
{
    if (_llist.size() < 1)
    {
        return std::nullopt;
    }
    return _llist.removeHead();
}
#endif
