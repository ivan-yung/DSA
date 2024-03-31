#ifndef TREE_SET_CPP
#define TREE_SET_CPP

#include "TreeSet.hpp"
#include <stack>
#include <queue>
#include <iostream>

template <typename T>
TreeSet<T>::TreeSet() : _root(nullptr), _size(0)
{
    _comparator = [](T left, T right)
    {
        if (left < right)
        {
            return -1;
        }
        else if (left > right)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    };
}

// TODO: Implement all methods defined in TreeSet.hpp here

template <typename T>
TreeSet<T>::TreeSet(const std::vector<T> &items) : _root(nullptr), 
    _comparator([](const T &left, const T &right)
    { return left < right ? -1 : (left > right ? 1 : 0); }),_size(0){
    for (const T &item : items)
    {
        add(item);
    }
}

template <typename T>
TreeSet<T>::TreeSet(std::function<int(T, T)> comparator) : _root(nullptr), _comparator(comparator), _size(0) {}

template <typename T>
TreeSet<T>::TreeSet(const std::vector<T> &items, std::function<int(T, T)> comparator) : _root(nullptr), _comparator(comparator), _size(0)
{
    for (const T &item : items)
    {
        add(item);
    }
}

template <typename T>
void TreeSet<T>::rotate_left(BinaryTreeNode<T> *x) {
    BinaryTreeNode<T> *y = x->_right;
    x->_right = y->_left;
    if (y->_left != nullptr){
        y->_left->_parent = x;
    }
    y->_parent = x->_parent;
    if (x->_parent == nullptr) {
        _root = y;
    } else if (x == x->_parent->_left) {
        x->_parent->_left = y;
    } else {
        x->_parent->_right = y;
    }
    y->_left = x;
    x->_parent = y;
}

template <typename T>
void TreeSet<T>::rotate_right(BinaryTreeNode<T> *y) {
    BinaryTreeNode<T> *x = y->_left;
    y->_left = x->_right;
    if (x->_right != nullptr) {
        x->_right->_parent = y;
    }
    x->_parent = y->_parent;
    if (y->_parent == nullptr) {
        _root = x;
    } else if (y == y->_parent->_left) {
        y->_parent->_left = x;
    } else {
        y->_parent->_right = x;
    }
    x->_right = y;
    y->_parent = x;
}

template <typename T>
void TreeSet<T>::fix_violation(BinaryTreeNode<T> *z)
{
    while (z != _root && z->_parent->_color == Red) {
        if (z->_parent == z->_parent->_parent->_left) {
            BinaryTreeNode<T> *y = z->_parent->_parent->_right;
            if (y != nullptr && y->_color == Red) {
                z->_parent->_color = Black;
                y->_color = Black;
                z->_parent->_parent->_color = Red;
                z = z->_parent->_parent;
            } else {
                if (z == z->_parent->_right) {
                    z = z->_parent;
                    rotate_left(z);
                }
                z->_parent->_color = Black;
                z->_parent->_parent->_color = Red;
                rotate_right(z->_parent->_parent);
            }
        } else {
            BinaryTreeNode<T> *y = z->_parent->_parent->_left;
            if (y != nullptr && y->_color == Red) {
                z->_parent->_color = Black;
                y->_color = Black;
                z->_parent->_parent->_color = Red;
                z = z->_parent->_parent;
            } else {
                if (z == z->_parent->_left) {
                    z = z->_parent;
                    rotate_right(z);
                }
                z->_parent->_color = Black;
                z->_parent->_parent->_color = Red;
                rotate_left(z->_parent->_parent);
            }
        }
    }
    _root->_color = Black;

}


template <typename T>
size_t TreeSet<T>::size() const
{
    return _size;
}

template <typename T>
void TreeSet<T>::add(T value)
{
    BinaryTreeNode<T> *newnode = new BinaryTreeNode<T>(value);
    newnode->_color = Red;

    if (is_empty())
    {
        newnode->_color = Black;
        _root = newnode;

    }
    else
    {
        // prev points to parent of curr
        BinaryTreeNode<T> *y = nullptr;
        BinaryTreeNode<T> *x = _root;
        while (x != nullptr)
        {
            y = x;
            if (_comparator(value, x->value) > 0)
            {
                x = x->_right;
            }
            else if (_comparator(value, x->value) < 0)
            {
                x = x->_left;
            }
            else
            {
                // this accounts for when the value already exists
                // current new node to be added is then deleted
                x->value = value;
                delete newnode;
                return;
            }
        }
        // this code links the new node to the parent, finishing the add operation
        newnode->_parent = y;
        if (_comparator(value, y->value) > 0)
        {
            y->_right = newnode;
        }
        else
        {
            y->_left = newnode;
        }
        
    }
    fix_violation(newnode);
    ++_size;
}
template <typename T>
bool TreeSet<T>::contains(T value) const
{
    // Create curr pointer
    BinaryTreeNode<T> *curr = _root;
    // loop through, if value is bigger, go right, if its smaller go left
    while (curr != nullptr)
    {
        if (_comparator(value, curr->value) > 0)
        {
            curr = curr->_right;
        }
        else if (_comparator(value, curr->value) < 0)
        {
            curr = curr->_left;
        }
        else
        {
            return true;
        }
    }
    return false;
}

template <typename T>
bool TreeSet<T>::is_empty() const
{
    if ((_root == nullptr) || (_size == 0))
    {
        return true;
    }
    return false;
}

template <typename T>
std::optional<T> TreeSet<T>::min() const
{
    BinaryTreeNode<T> *curr = _root;

    if (_root == nullptr)
    {
        return std::nullopt;
    }

    while (curr->_left != nullptr)
    {
        curr = curr->_left;
    }
    return std::make_optional(curr->value);
}

template <typename T>
std::optional<T> TreeSet<T>::max() const
{
    BinaryTreeNode<T> *curr = _root;

    if (_root == nullptr)
    {
        return std::nullopt;
    }

    while (curr->_right != nullptr)
    {
        curr = curr->_right;
    }
    return std::make_optional(curr->value);
}

// non recursive approach
template <typename T>
std::vector<T> TreeSet<T>::to_vector() const
{
    std::vector<T> container;
    if (_size == 0)
    {
        return container;
    }
    std::stack<BinaryTreeNode<T> *> stack;
    BinaryTreeNode<T> *curr = _root;
    while (curr != nullptr || !stack.empty())
    {
        while (curr != nullptr)
        {
            stack.push(curr);
            curr = curr->_left;
        }
        curr = stack.top();
        stack.pop();
        container.push_back(curr->value);
        curr = curr->_right;
    }

    return container;
}

template <typename T>
std::optional<T> TreeSet<T>::get(T value) const
{
    BinaryTreeNode<T> *curr = _root;
    while (curr != nullptr)
    {
        if (_comparator(value, curr->value) < 0)
        {
            curr = curr->_left;
        }
        else if (_comparator(value, curr->value) > 0)
        {
            curr = curr->_right;
        }
        else
        {
            return curr->value;
        }
    }
    return std::nullopt;
}


template <typename T>
TreeSet<T> TreeSet<T>::operator+(const TreeSet<T> &other){
    TreeSet<T> total(_comparator);
    std::vector<T> temptotal;
    std::vector<T> s1 = to_vector();
    std::vector<T> s2 = other.to_vector();
    for(int i = 0; i < s1.size(); i++){
        temptotal.push_back(s1[i]);
    }
    for(int i = 0; i < s2.size(); i++){
        temptotal.push_back(s2[i]);
    }
    for(int i = 0; i < temptotal.size(); i++){
        total.add(temptotal[i]);
    }
    return total;
}

template <typename T>
TreeSet<T> &TreeSet<T>::operator+=(const TreeSet<T> &other){
    std::vector first = this->to_vector();
    std::vector second = other.to_vector();

    for (int i = 0; i < second.size(); i++) {
        this->add(second[i]);
    }

    return *this;

}

template <typename T>
TreeSet<T> TreeSet<T>::operator&(const TreeSet &other){
    /*
    TreeSet<T> total(_comparator);
    std::vector first = to_vector();
    std::vector second = other.to_vector();
    int min;
    if (first.size() < second.size()){
        min = first.size();
    }else{
        min = second.size();
    }
    for (int i = 0; i < min; i++) {
        if (contains(first[i]) && other.contains(second[i])) {
            total.add(first[i]);
        }
    }
    return total;*/
    TreeSet<T> total(_comparator);
    std::vector first = to_vector();
    std::vector second = other.to_vector();
    for(int i = 0, j = 0; i < first.size() && j < second.size();){
        if (first[i] == second[j]){
            total.add(first[i]);
            ++i;
            ++j;
        }
        else if (first[i] < second[j]){
            ++i;
        }
        else {
            ++j;
        }
    }
    return total;
}

template <typename T>
bool TreeSet<T>::operator==(const TreeSet &other) const{
    std::vector first = to_vector();
    std::vector second = other.to_vector();
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());
    if (first.size() != second.size()){
        return false;
    }
    int count;
    for(int i = 0; i < first.size(); i++){
        if(first[i] != second[i]){
            return false;
        }
    }  
    return true;      
}

template <typename T>
bool TreeSet<T>::operator!=(const TreeSet &other) const{
    TreeSet<T> first(_comparator);
    std::vector temp = to_vector();
    for(int i = 0; i < _size; i++){
        first.add(temp[i]);
    }
    if (first == other){
        return false;
    } else{
        return true;
    }

}
template <typename T>
void TreeSet<T>::clear()
{
    if (_size == 0){
        return;
    }
    if (_root == nullptr){
        return;
    }
    /*
    std::stack<BinaryTreeNode<T> *> stack;
    BinaryTreeNode<T> *curr = _root;
    BinaryTreeNode<T> *parent = nullptr

    while((curr != nullptr) || !stack.empty()){
        if (curr){
            stack.push(curr);
            curr = curr->left;
        }else{
            curr = stack.top();
            if ((curr->_right) && curr->_right ){

            }
        }
    }*/
    // function uses a queue to keep track of the BFS traversal, and deleting each node
    std::queue<BinaryTreeNode<T>*> queue;
    queue.push(_root);
    while(!queue.empty()){
        //curr pointer points to root
        BinaryTreeNode<T> * curr = queue.front();
        queue.pop();
        if (curr->_left != nullptr){
            queue.push(curr->_left);
        }
        if (curr->_right != nullptr){
            queue.push(curr->_right);
        }
        delete curr;
        --_size;
    }
    _root = nullptr;

}

template <typename T>
TreeSet<T>::~TreeSet()
{
    clear();
}

#endif
