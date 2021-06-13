#ifndef HW2_SORTEDLIST_H
#define HW2_SORTEDLIST_H

#include <iostream>
#include <string>
#include "stdlib.h"

const string OUT_OF_RANGE_ERROR = "End of list";

template <class T>
class SortedList
{
    typedef class node_t
    {
    public:
        T data;
        class node_t *next;

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
        const Node& operator*();
    };

    SortedList();
    ~SortedList();
    SortedList(const SortedList<T> &list);
    SortedList<T>& operator= (const SortedList<T> &list);
    SortedList<T> copyParameters(const SortedList<T> &list);
    void insert(const T new_data);
    void remove(const_iterator iterator) const;
    int length();

    template <class Condition>
    SortedList<T>& filter(Condition condition) const;

    template <class Function>
    SortedList<T>& apply(Function function) const;

    const_iterator begin();
    const_iterator end();
};

template<class T>
SortedList<T>::const_iterator::const_iterator() : current_node(NULL)
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
    if (current_node->next == NULL)
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
const typename SortedList<T>::Node& SortedList<T>::const_iterator::operator*()
{
    return current_node;
}

template<class T>
SortedList<T>::SortedList() : head(NULL), size(0)
{
}

template<class T>
SortedList<T>::~SortedList()
{
    if(size == 1)
    {
        delete(head);
    }
    else if(size > 1) {
        Node current_node = head->next;
        Node to_delete = head;
        while (current_node != NULL)
        {
            current_node = current_node->next;
            delete (to_delete);
        }
        delete(to_delete);
    }
}

template<class T>
SortedList<T>::SortedList(const SortedList<T> &list)
{
    copyParameters(list);
}

template<class T>
SortedList<T>& SortedList<T>::operator= (const SortedList<T> &list)
{
    if(this == &list)
    {
        return *this;
    }
    if(size > 1)
    {
        Node to_delete = head;
        Node current_node = head->next;
        while (current_node != NULL)
        {
            to_delete = current_node;
            current_node = current_node->next;
            delete (to_delete);
        }
        head = NULL;
    } else if(size == 1)
    {
        delete(head);
        head = NULL;
    }
    SortedList<T> new_list = copyParameters(list);
    new_list.iterator = list.iterator;
    return &new_list;
}

template<class T>
SortedList<T> SortedList<T>::copyParameters(const SortedList<T> &list)
{
    size = list.size;
    if(size == 0)
    {
        head = NULL;
        return *this;
    }

    Node new_node;
    Node current_node = list.head;
    head = new_node;
    for(int i = 0; i < size-1; i++)
    {
        new_node->data = current_node->data;
        Node next_node;
        new_node->next = next_node;
        new_node = new_node->next;
    }
    new_node->data = current_node->data;
    new_node->next = NULL;

    return *this;
}

template<class T>
void SortedList<T>::insert(const T new_data)
{
    Node runner = head;
    while(runner->next->data < new_data)
    {
        runner = runner->next;
    }

    Node new_node;
    new_node->data = new_data;
    new_node->next = runner->next;
    runner->next = new_node;

    size = size + 1;
}

template<class T>
void SortedList<T>::remove(const_iterator iterator) const
{
    if(iterator.current_node->data == head->data)
    {
        delete(head);
        head = NULL;
    }
    Node current_node = head;
    while(current_node->next->data != iterator.current_node->data)
    {
        current_node = current_node->next;
    }

    delete(current_node->next);
    current_node->next = current_node->next->next;
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
    SortedList<T> new_list = new SortedList<T>();
    if(size == 0)
    {
        return new_list;
    }
    Node new_node = NULL;
    Node next_node = NULL;
    new_list.head = new_node;
    while(current_node != NULL)
    {
        if (condition(current_node->data))
        {
            new_node = new Node();
            new_node->data = current_node->data;
            next_node = new Node();
            new_node->next = next_node;
        }
        current_node = current_node->next;
        new_node = new_node->next;
    } // List is already sorted so new list has to be sorted too

    if(next_node != NULL)
    {
        delete(next_node);
    }

    return new_list;
}

template<class T>
template <class Function>
SortedList<T>& SortedList<T>::apply(Function function) const
{
    Node current_node = head;
    SortedList<T> new_list = SortedList<T>();
    if(size == 0)
    {
        return &new_list;
    }

    Node new_node = new Node();
    new_list.head = new_node;

    while(current_node != NULL)
    {
        new_node->data = function(current_node->data);
        Node next_node = new Node();
        new_node->next = next_node;
        current_node = current_node->next;
        next_node = new_node->next;
        if(current_node == NULL)
        {
            delete(next_node);
        }
    }
    return &new_list;
}

template<class T>
typename SortedList<T>::const_iterator SortedList<T>::begin()
{
    return const_iterator();
}

template<class T>
typename SortedList<T>::const_iterator SortedList<T>::end()
{
    const_iterator iterator = begin();
    Node runner = head;
    while(iterator.current_node->next != NULL)
    {
        iterator.current_node = iterator.current_node->next;
    }
    return iterator;
}

#endif //HW2_SORTEDLIST_H
