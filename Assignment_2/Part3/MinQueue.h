#include <iostream>
#include <string>
#include <stdexcept>
#include "TemplatedDLList.h"
using namespace std;

template <typename T>

class MinQueue
{
    public:
        MinQueue() : list() { count = 0; }
        void enqueue(T x); //adds an element to the queue and sorts it from small to largest
        T dequeue(); //deletes the smallest element
        int size(); //returns the size of the queue
        bool is_empty(); //returns true if queue is empty and false if otherwise
        T min(); //returns the smallest element without deleting it
        void print(); //prints out the list
    private:
        DLList<T> list;
        int count; //size of queue
};

template <typename T>
void MinQueue<T>::enqueue(T x)
{
    list.insert_last(x);
    count++;
}

template <typename T>
T MinQueue<T>::dequeue()
{
    if(list.is_empty())
    {
        throw "Empty Queue";
    }
    count--;
    return list.remove_first();
}

template <typename T>
int MinQueue<T>::size()
{
    return this->count;
}

template <typename T>
bool MinQueue<T>::is_empty()
{
    return list.is_empty();
}

template <typename T>
T MinQueue<T>::min()
{
    DLListNode<T> *node = list.first_node();
    T min = node->obj;
    while(node != list.after_last_node())
    {
        if(min > node->obj)
        {
            min = node->obj;
        }
        node = node->next;
    }

    return min;
}

template <typename T>
void MinQueue<T>::print()
{
    cout << list;
}