/*
    Name: Evan Garcia, 5007529509, 1002, #1
    Description: Functions for a linked list
    Input: other cpp files
    Output: running the other files
*/
#include "LL.h"
#include <string>
#include <cstdlib>

template <class T>
LL<T>::LL()
{
    head = nullptr;
    tail = nullptr;
}

template <class T>
LL<T>::LL(const LL<T>& copy)
{
    //copy the linked list
    head = nullptr;
    tail = nullptr;
    Iterator it;
    it = copy.begin(); //iterator iterating through copy

    while (it.current != nullptr)
    {
        push_back(it.current->data);
        it++;
    }
}

template <class T>
const LL<T>& LL<T>::operator=(const LL<T>& rhs)
{
    Iterator r_it;
    r_it = rhs.begin(); //iterator iterating through rhs
    
    //delete everything in this first
    Node *cur = head;
    while (cur != nullptr)
    {
        Node *next = cur->next;  // save before delete
        delete cur;
        cur = next;
    }
    head = nullptr;
    tail = nullptr;

    //copy from rhs
    while (r_it.current != nullptr)
    {
        push_back(r_it.current->data);
        r_it++;
    }

    return *this;
}

template <class T>
LL<T>::~LL()
{
    Node *cur = head;
    while (cur != nullptr)
    {
        Node *next = cur->next;  // save before delete
        delete cur;
        cur = next;
    }
    head = nullptr;
    tail = nullptr;
}


template <class T>
void LL<T>::push_front(const T& item)
{
    //push_back() but opposite
    Node *tmp;
    tmp = new Node;
    tmp->data = item;
    if (head != nullptr && tail != nullptr)
    {
        head->prev = tmp;
        tmp->next = head;
        tmp->prev = nullptr;
        head = tmp;
        tmp = nullptr;
    } 
    if (head == nullptr && tail == nullptr)
    {
        //The case in which there are no nodes in the list
        tail = tmp;
        head = tmp;
        tmp->prev = nullptr;
        tmp->next = nullptr;
    }
}

template <class T>
void LL<T>::push_back(const T& item)
{
/*  Code from class 
    node * tmp;
    tmp = new node;
    (*tmp).data = x; not tmp.data or *tmp.data
    or you can do
    tmp->data = x; it is the same

    COMMON ERROR!!!
    tail = tmp;
    
    tail->next = tmp; points the tail next pointer to tmp
    temp->prev = tail; points the temp prev pointer to tail
    tmp->next = nullptr; points the temp next pointer to nullptr
    tail = tmp;

    delete tmp; -> Deletes everything we did! DONT DO THIS!!!!
    do this 
    tmp = nullptr;

    make code in case there is an empty linked list
    if head and tail == null -> just add the node as the new tail and head
*/
    Node *tmp;
    tmp = new Node;
    tmp->data = item;
    if (head != nullptr && tail != nullptr)
    {
        tail->next = tmp;
        tmp->prev = tail;
        tmp->next = nullptr;
        tail = tmp;
        tmp = nullptr;
    }
    if (head == nullptr && tail == nullptr)
    {
        //The case in which there are no nodes in the list
        tail = tmp;
        head = tmp;
        tmp->prev = nullptr;
        tmp->next = nullptr;
    }
}

template <class T>
void LL<T>::pop_front()
{
/*  Code from class
    node *tmp;

    don't do
    tmp = new node
    tmp = head

    just do
    tmp = head;

    head = head->next; points the head pointer to the node next to the head
    delete tmp; destroys the previous head node

    head->prev = nullptr; finalize the new head
*/
    if (head == nullptr && tail == nullptr) // if the list is empty, return
    {
        return;
    }
    if (head == tail) // if there is one node
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node *tmp;
    tmp = head;
    head = head->next;
    delete tmp;
    head->prev = nullptr;
}

template <class T>
void LL<T>::pop_back()
{
    //Just the direct opposite of pop_front()
    if (head == nullptr && tail == nullptr) // if the list is empty, return
    {
        return;
    }
    if (head == tail) // if there is one node
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node *tmp;
    tmp = tail;
    tail = tail->prev;
    delete tmp;
    tail->next = nullptr;

}

template <class T>
void LL<T>::removeNode(LL<T>::Iterator& it)
{
// Removes the node it points to
    Node *x;
    Node *y;
    Node *tmp;
    tmp = it.current;
    x = tmp->prev;
    y = tmp->next;
    if (x == nullptr && y == nullptr) //if empty return
    {
        return;
    }
    if (x == nullptr) //if head, call pop_front
    {
        pop_front();
        it.current = y;
        return;
    }
    if (y == nullptr)//if tail, pop_back
    {
        pop_back();
        it.current = x;
        return;
    }

    x->next = y;
    y->prev = x;
    it.current = y; //swap then set the current to the next option

    delete tmp;
}

template <class T>
void LL<T>::insertNode(const LL<T>::Iterator& it, const T& item)
{
// Inserts a new node after the node iterator it points to and fills the new node's
// data slot with item
    Node *tmp;
    tmp = new Node;
    tmp-> data = item; //set the temp node

    Node *x;
    x = it.current->next;//temp node that points to the next node
    if (x == nullptr)
    {
        this->push_back(item);
        return;
    }
    it.current->next = tmp;
    tmp->next = x;
    x->prev = tmp;
    tmp->prev = it.current;//switch stuff around

}

template <class T>
void LL<T>::swap(LL<T>::Iterator& i, LL<T>::Iterator& j)
{
    /*Class Code
    new nodes i_left, i_right, j_left, j_right
    */
	Node *a; //points to i->prev
    Node *b; //points to i->next
    Node *x; //points to j->prev
    Node *y; //points to j->next
    Node *tmp; //used to swap pointers
    a = i.current->prev;
    b = i.current->next;
    x = j.current->prev;
    y = j.current->next;

    //first swap
    if (a != nullptr) //i is a not head
    {
        a->next = j.current;
        j.current->prev = a;
    }
    else //j is a head
    {
        head = j.current;
        j.current->prev = nullptr;
    }
    if (b == j.current) //right next to eachother
    {
        j.current->next = i.current;
        i.current->prev = j.current; //connects the two nodes

        if (y != nullptr) //if y exists
        {
            i.current->next = y;
            y->prev = i.current;
        }
        else //i is the tail
        {
            tail = i.current;
            i.current->next = nullptr;
        }

        tmp = i.current;
        i.current = j.current;
        j.current = tmp;
        return;
    }

    b->prev = j.current;
    j.current->next = b;

    //next swap
    x->next = i.current;
    i.current->prev = x;
    if (y!= nullptr)
    {
        i.current->next = y;
        y->prev = i.current;
    }
    else
    {
        tail = i.current;
        i.current->next = nullptr;
    }

    tmp = i.current;
    i.current = j.current;
    j.current = tmp;

}

template class LL<int>;
template class LL<std::string>;

