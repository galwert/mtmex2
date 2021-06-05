//
// Created by galwe on 05/06/2021.
//

#ifndef HW2_SORTEDLIST_H
#define HW2_SORTEDLIST_H
#include <iostream>
#include <string>
template <class T>

class SortedList
{
    typedef struct node_t{
        T data;
        struct node_t *next;
    } *Node;

private:
Node* head;

public:
    SortedList<T>();
    SortedList<T>& operator=(const SortedList& sortedList)=default;
};

template<class T>
SortedList<T>::SortedList()
{
    head=NULL;
}


#endif //HW2_SORTEDLIST_H
