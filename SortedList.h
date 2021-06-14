#ifndef HW2_SORTEDLIST_H
#define HW2_SORTEDLIST_H

#include <iostream>
#include <string>
#include "stdlib.h"

const std::string OUT_OF_RANGE_ERROR = "End of list";

template <class T>
class SortedList
{
    typedef class node_t
    {
    public:
        T data;
        class node_t *next;

        node_t(T data);

    } *Node;

public:
    Node head;
    int size;

    class const_iterator
    {
        friend class SortedList<T>;

    public:
        Node current_node;

    private:
        const_iterator();
        const_iterator(const SortedList<T>::Node node_to_be_head);

    public:
        const_iterator(const SortedList<T>::const_iterator &iterator_to_copy);
        const_iterator& operator= (const const_iterator &iterator_to_assign);
        void operator++();
        bool operator==(const const_iterator &iterator1) const;
        const T operator*();
    };

    SortedList();
    ~SortedList();
    SortedList(const SortedList<T> &list);
    void operator= (const SortedList<T> &list);
    void insert(const T& new_data);
    void remove(const_iterator iterator);
    int length();

    template <class Condition>
    SortedList<T>& filter(Condition condition) const;

    template <class Function>
    SortedList<T> apply(Function function) const;

    const_iterator begin();
    const_iterator end();
};

template<class T>
SortedList<T>::node_t::node_t(T data) : data(data), next(nullptr)
{
}

template<class T>
SortedList<T>::const_iterator::const_iterator() : current_node(head)
{
}

template<class T>
SortedList<T>::const_iterator::const_iterator(const SortedList<T>::Node node_to_be_head) : current_node(node_to_be_head)
{
}

template<class T>
SortedList<T>::const_iterator::const_iterator(const SortedList<T>::const_iterator &iterator_to_copy) :
    current_node(iterator_to_copy.current_node)
{
}

template<class T>
typename SortedList<T>::const_iterator&
                SortedList<T>::const_iterator::operator= (const const_iterator &iterator_to_assign)
{
    current_node = iterator_to_assign.current_node;
    return *this;
}

template<class T>
void SortedList<T>::const_iterator::operator++()
{
    if (current_node->next == nullptr)
    {
        throw std::out_of_range(OUT_OF_RANGE_ERROR);
    }

    current_node = current_node->next;
}

template<class T>
bool SortedList<T>::const_iterator::operator==(const const_iterator &iterator1) const
{
    return current_node == iterator1.current_node;
}

template<class T>
const T SortedList<T>::const_iterator::operator*()
{
    return current_node->data;
}

template<class T>
SortedList<T>::SortedList() : head(nullptr), size(0)
{
}

template<class T>
SortedList<T>::~SortedList()
{
    const_iterator iterator = begin();

    while(!(iterator == nullptr))
    {
        remove(iterator);
        ++iterator;
    }
}

template<class T>
SortedList<T>::SortedList(const SortedList<T>& list)
{
    size = list.size;
    if(size == 0)
    {
        head = nullptr;
        return;
    }

    Node current_node = list.head;
    while(current_node != nullptr)
    {
        insert(current_node->data);
        current_node = current_node->next;
    }
}

template<class T>
void SortedList<T>::operator= (const SortedList<T> &list)
{
    if(this == &list)
    {
        return;
    }
    if(size > 1)
    {
        Node to_delete = head;
        Node current_node = head->next;
        while (current_node != nullptr)
        {
            delete (to_delete);
            to_delete = current_node;
            current_node = current_node->next;
        }
        head = nullptr;
    }
    else if(size == 1)
    {
        delete(head);
        head = nullptr;
    }

    size = 0;
    if(list.size == 0)
    {
        head = nullptr;
        return;
    }

    Node current_node = list.head;
    while(current_node != nullptr)
    {
        insert(current_node->data);
        current_node = current_node->next;
    }
}

template<class T>
void SortedList<T>::insert(const T& new_data)
{
    Node new_node = new node_t(new_data);
    if(size == 0)
    {
        head = new_node;
    }
    else if (size == 1)
    {
        if(head->data < new_data)
        {
            head->next = new_node;
        }
        else
        {
            new_node->next = head;
            head = new_node;
        }
    }
    else
    {
        if(!(head->data < new_data))
        {
            new_node->next = head;
            head = new_node;
            size = size + 1;
            return;
        }

        Node current_node = head->next;
        Node node_before = head;
        while(current_node && current_node->data < new_data)
        {
            current_node = current_node->next;
            node_before = node_before->next;
        }

        if(current_node == nullptr)
        {
            node_before->next = new_node;
            new_node->next = nullptr;
            size = size + 1;
            return;
        }

        node_before->next = new_node;
        new_node->next = current_node;
    }

    size = size + 1;
}

template<class T>
void SortedList<T>::remove(const_iterator iterator)
{
    if(size == 0)
    {
        return;
    }
    else if(size == 1)
    {
        delete(head);
        head = nullptr;
        size = size - 1;
        return;
    }
    else
    {

    }
}

template<class T>
int SortedList<T>::length()
{
    return size;
}

template<class T>
template <class Condition>
SortedList<T>& SortedList<T>::filter(Condition condition) const
{
    Node current_node = head;
    SortedList<T> new_list = SortedList<T>();
    if(size == 0)
    {
        return new_list;
    }
    Node new_node;
    Node next_node;
    new_list.head = new_node;
    while(current_node != nullptr)
    {
        if (condition(current_node->data))
        {
            new_node = new node_t(current_node->data);
            next_node = Node();
            new_node->next = next_node;
        }
        current_node = current_node->next;
        new_node = new_node->next;
    } // List is already sorted so new list has to be sorted too

    if(next_node != nullptr)
    {
        delete(next_node);
    }

    return new_list;
}

template<class T>
template <class Function>
SortedList<T> SortedList<T>::apply(Function function) const
{
    Node current_node = head;
    SortedList<T> new_list;
    if(size == 0)
    {
        return new_list;
    }

    while(current_node != nullptr)
    {
        new_list.insert(function(current_node->data));
        current_node = current_node->next;
    }

    return new_list;
}

template<class T>
typename SortedList<T>::const_iterator SortedList<T>::begin()
{
    return const_iterator(head);
}

template<class T>
typename SortedList<T>::const_iterator SortedList<T>::end()
{
    const_iterator iterator = begin();
    while(iterator.current_node->next != nullptr)
    {
        iterator.current_node = iterator.current_node->next;
    }
    return iterator;
}

#endif //HW2_SORTEDLIST_H
