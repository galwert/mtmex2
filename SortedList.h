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

        node_t(T insert_data, node_t next_node)
        {
            data = insert_data;
            next = next_node;
        }
    } *Node;

public:
    class const_iterator
    {
    public:
        Node current_node;

    private:
        const_iterator()
        {
            Node current_node = head;
        }

    public:
        const_iterator(const SortedList<T>::const_iterator &iterator_to_copy)
        {
           current_node = iterator_to_copy.current_node;
        }

        ~const_iterator()
        {
            return;
        }

        const_iterator& operator=(const const_iterator &iterator_to_assign)
        {
            current_node = iterator_to_assign.current_node;
            return *this;
        }

        void operator++ ()
        {
            if(current_node->next == NULL)
            {
                throw std::out_of_range(OUT_OF_RANGE_ERROR);
            }

            current_node = current_node->next;
        }

        bool operator== (const const_iterator& iterator1) const
        {
            return current_node == iterator1.current_node;
        }

        const T& operator* ()
        {
            T iterator_data = *current_node;
            return *iterator_data;
        }
    };

private:
    Node head;
    int size;

public:
    SortedList()
    {
        head = NULL;
        size = 0;
    }

    ~SortedList()
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

    SortedList(const SortedList<T> &list)
    {
        copyParameters(list);
    }

    SortedList<T>& operator= (const SortedList<T> &list)
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
        return &new_list;
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

        return *this;
    }

    void insert(const T new_data)
    {
        Node runner = head;
        while(runner->next->data < new_data)
        {
            runner = runner->next;
        }

        Node new_node (new_data, runner->next);
        runner->next = new_node;

        size = size + 1;
    }

    void remove(const_iterator iterator) const
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
    SortedList<T>& apply(Function function) const
    {
        Node current_node = head;
        SortedList<T> new_list = SortedList<T>();
        if(size == 0)
        {
            return *new_list;
        }

        Node new_node = new Node();
        new_list.head = new_node;

        while(current_node != NULL)
        {
            new_node->data = function(current_node);
            Node next_node = new Node();
            new_node->next = next_node;
            current_node = current_node->next;
            next_node = new_node->next;
            if(current_node == NULL)
            {
                delete(next_node);
            }
        }
        return *new_list;
    }

    const_iterator& begin()
    {
        const_iterator new_iterator = new const_iterator();
        return *new_iterator;
    }

    const_iterator& end()
    {
        const_iterator new_iterator();
        Node current_node = head;
        while(current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        new_iterator.current_node = current_node;
        return new_iterator;
    }
};

#endif //HW2_SORTEDLIST_H
