#ifndef HW2_SORTEDLIST_H
#define HW2_SORTEDLIST_H

#include <iostream>
#include <string>

template <class T>

class SortedList
{
    typedef struct node_t
    {
        T data;
        struct node_t *next;
    } *Node;

    class const_iterator
    {
        // iterator part
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

    void insert(T new_data)
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

    void remove(T iterator)
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
};

#endif //HW2_SORTEDLIST_H
