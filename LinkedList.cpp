#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "LinkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList() : _size(0), _head(nullptr), _tail(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&other) : _size(other._size),
                                                   _head(other._head),
                                                   _tail(other._tail)
{
    other._size = 0;
    other._head = nullptr;
    other._tail = nullptr;
}

// TODO: Implement all other methods defined in LinkedList.hpp here

template <typename T>
size_t LinkedList<T>::size() const
{
    return _size;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::head() const
{
    return _head;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::tail() const
{
    return _tail;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::find(T value) const
{
    LinkedListNode<T> *curr = _head;
    while (curr != nullptr)
    {
        if (curr->value == value)
        {
            return curr;
        }
        curr = curr->_next;
    }
    return nullptr;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::prepend(T value)
{
    LinkedListNode<T> *newnode = new LinkedListNode(value);

    if (_size == 0)
    {
        _tail = newnode;
        _head = newnode;
        ++_size;
    }
    else if (_size == 1)
    {
        _head = newnode;
        _head->_next = _tail;
        ++_size;
    }
    else
    {
        newnode->_next = _head;
        _head = newnode;
        ++_size;
        return _head;
    }

    return _head;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::append(T value)
{
    LinkedListNode<T> *newnode = new LinkedListNode(value);
    if (_tail == nullptr)
    {
        _head = newnode;
        _tail = newnode;
    }
    else
    {
        _tail->_next = newnode;
        _tail = newnode;
    }
    ++_size;
    return _tail;
}

template <typename T>
LinkedListNode<T> *LinkedList<T>::insertAfter(LinkedListNode<T> *node, T value)
{
    if (_size == 0){
        return prepend(value);
    }
    if (node == nullptr)
    {
        return prepend(value);
    }
    LinkedListNode<T> *newnode = new LinkedListNode(value);
    newnode->value = value;
    newnode->_next = node->_next;
    node->_next = newnode;
    ++_size;
    return newnode;
}

template <typename T>
std::optional<T> LinkedList<T>::removeHead()
{
    if (_size == 0){
        return std::nullopt;
    }
    if (_head == nullptr)
    {
        return std::nullopt;
    }
    if (_size == 1)
    {
        _tail = nullptr;

    }
    LinkedListNode<T> *curr = _head;
    T value = _head->value;
    _head = _head->_next;
    delete (curr);
    --_size;

    return value;
}

template <typename T>
bool LinkedList<T>::remove(T value)
{
    LinkedListNode<T> *curr = _head;
    LinkedListNode<T> *prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->value == value)
        {
            if (curr == _head){
                removeHead();
                return true;
            }
            if (curr == _tail)
            {

                _tail = prev;
                delete (curr);
                --_size;
                return true;
            }
            if (_size == 2)
            {
                if (curr == _head)
                {
                    _head = _tail;
                    delete curr;
                    --_size;
                    return true;
                }
                if (curr == _tail)
                {
                    _tail = _head;
                    delete curr;
                    --_size;
                    return true;
                }
            }
            else
            {
                prev->_next = curr->_next;
                delete (curr);
                --_size;
                return true;
            }
        }
        prev = curr;
        curr = curr->_next;
    }
    return false;
}

template <typename T>
void LinkedList<T>::clear()
{
    while (removeHead())
    {
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}
template <typename T>
LinkedList<T>::LinkedList(const std::vector<T> &items)
{

    _size = 0;
    _head = nullptr;
    _tail = nullptr;

    for (const T &item : items)
    {
        append(item);
    }
}

#endif
