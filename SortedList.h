#ifndef HW2_SORTEDLIST_H
#define HW2_SORTEDLIST_H

#include <iostream>
#include <string>
#include "stdlib.h"

template <class T>

class SortedList
{
    typedef class node_t
    {
        T data = NULL;
        class node_t *next = NULL;
    } *Node;

    class const_iterator
    {
    private:
        Node current_node;

        const_iterator()
        {
            Node current_node = head;
        }

    public:
        const_iterator(const SortedList<T>::const_iterator &iterator_to_copy)
        {
            iterator.current_node = iterator_to_copy.current_node;
        }

        ~const_iterator()
        {
            return;
        }

        const_iterator& const_iterator::operator=(const const_iterator() &iter_to_assign)
        {
            iterator.current_node = iterator_to_assign.current_node;
            return *this;
        }

        void operator++ ()
        {
            if(iterator.current_node->next == NULL)
            {
                throw std::out_of_range;
            }
            iterator.current_node = iterator.current_node->next;
        }

        bool operator== (const const_iterator& iterator1) const
        {
            return iterator.current_node == iterator1.current_node;
        }

        const const_iterator& SortedList<T>::const_iterator::operator* ()
        {
            SortedList<T>::const_iterator iterator_data = *iterator.current_node;
            return iterator_data;
        }
    };

private:
    Node head;
    int size;
    const_iterator iterator;

public:
    SortedList()
    {
        head = NULL;
        size = 0;
        iterator = head;
    }

    ~SortedList()
    {
        if(size == 1)
        {
            delete(head);
        }
        else if(size > 1) {
            Node iterator = head->next;
            Node to_delete = head;
            while (iterator != NULL)
            {
                iterator = iterator->next;
                delete (to_delete);
            }
            delete(to_delete);
        }
    }

    SortedList(const SortedList<T> &list)
    {
        copyParameters(list);
    }

    SortedList<T>& operator= (const SortedList<T> &list)
    {
        copyParameters(list);
        return *this;
    }

    SortedList<T> copyParameters(const SortedList<T> &list)
    {
        size = list.size;
        if(size == 0)
        {
            head = NULL;
            return *this;
        }

        Node new_node = new Node();
        Node current_node = list.head;
        head = new_node;
        for(int i = 0; i < size-1; i++)
        {
            new_node->data = current_node->data;
            Node next_node = new Node();
            new_node->next = next_node;
            new_node = new_node->next;
        }
        new_node->data = current_node->data;
        new_node->next = NULL;
    }

    void insert(T new_data) const
    {
        Node runner = head;
        while(runner->next->data < new_data)
        {
            runner = runner->next;
        }

        Node new_node = new Node();
        new_node->data = *new_data;
        new_node->next = runner->next;

        runner->next = new_node;

        size = size + 1;
    }

    void remove(T iterator) const
    {
        if(iterator == head->data)
        {
            delete(head);
            head = NULL;
        }
        Node current_node = head;
        while(current_node->next->data != iterator)
        {
            current_node = current_node->next;
        }

        delete(current_node->next);
        current_node->next = current_node->next->next;
    }

    int length()
    {
        return size;
    }

    template <class Condition>
    SortedList<T>& filter(Condition condition) const
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

    template <class Function>
    SortedList<T>& apply(SortedList<T> Function) const
    {
        Node current_node = head;
        SortedList<T> new_list = SortedList<T>();
        if(size == 0)
        {
            return new_list;
        }

        Node new_node = new Node();
        new_list.head = new_node;

        while(current_node != NULL)
        {
            new_node->data = Function(current_node);
            Node next_node = new Node();
            new_node->next = next_node;
            current_node = current_node->next;
            next_node = new_node->next;
            if(current_node == NULL)
            {
                delete(next_node);
            }
        }
        return new_list;
    }

    void begin(const_iterator iterator)
    {
        iterator.current_node = head;
    }

    void end(const_iterator iterator)
    {
        iterator = head;
        while(iterator.current_node->next != NULL)
        {
            iterator.current_node = iterator.current_node->next;
        }
    }
};

#endif //HW2_SORTEDLIST_H
