#ifndef TREE_MAP_CPP
#define TREE_MAP_CPP

#include "TreeMap.hpp"
#include "TreeSet.cpp"

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::TreeMap() : _tree([](const std::pair<TKey, TValue> &left, const std::pair<TKey, TValue> &right) {
    if (left.first < right.first) {
        return -1;
    } else if (left.first > right.first) {
        return 1;
    } else {
        return 0;
    }
}) {}

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::TreeMap(const std::vector<std::pair<TKey, TValue>> &items) : _tree(items, [](const std::pair<TKey, TValue> &left, const std::pair<TKey, TValue> &right) {
    if (left.first < right.first) {
        return -1;
    } else if (left.first > right.first) {
        return 1;
    } else {
        return 0;
    }
}) {}

template <typename TKey, typename TValue>
size_t TreeMap<TKey, TValue>::size() const
{
    return _tree.size();
}

template <typename TKey, typename TValue>
void TreeMap<TKey, TValue>::insert(TKey key, TValue value)
{
    _tree.add(std::make_pair(key, value));
}

template <typename TKey, typename TValue>
std::optional<TValue> TreeMap<TKey, TValue>::get(TKey key) const
{
    std::optional<std::pair<TKey, TValue>> get = _tree.get(std::make_pair(key, TValue()));
    if (get.has_value())
    {
        return get.value().second;
    }
    return {};
}

template <typename TKey, typename TValue>
bool TreeMap<TKey, TValue>::contains(TKey key) const
{
    return _tree.contains(std::make_pair(key, TValue{}));
}

template <typename TKey, typename TValue>
std::vector<std::pair<TKey, TValue>> TreeMap<TKey, TValue>::to_vector() const
{
    return _tree.to_vector();
}

template <typename TKey, typename TValue>
bool TreeMap<TKey, TValue>::is_empty() const
{
    return _tree.is_empty();
}

template <typename TKey, typename TValue>
void TreeMap<TKey, TValue>::clear()
{
    _tree.clear();
}

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::~TreeMap()
{
    clear();
}
#endif
