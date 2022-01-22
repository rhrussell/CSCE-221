#include <iostream>
#include <fstream>
#include "Stress_ball.h"
using namespace std;

#ifndef Collection_H
#define Collection_H

enum class Sort_choice {bubble_sort, insertion_sort, selection_sort};

struct Collection
{
    public:
        Collection(); //default constructor: Default size of collection is 8
        Collection(int s); //constructor with one arugment which is the required of the collection
        Collection(const Collection &c); //copy constructor: makes a copy of a collection
        Collection& operator=(const Collection &c); //copy assignment: overwrites an existing collection by another collection
        ~Collection(); //destructor: destroys a collection(deallocates allocated memeory, set to zero size and capacity)
        Collection(Collection&& c); //move constructor: efficiently creates a new collection from an existing one
        Collection& operator=(Collection&& c); //move assignment: efficiently copies a collection during an assignment
        void insert_item(const Stress_ball& sb); //insert stress ball to collection; if collection = full, double array size; use resize()
        bool contains(const Stress_ball& sb) const; //checks if a stress ball with a certain color or size is in the collection; returns true if it is
        Stress_ball remove_any_item(); //remove and return a random stress ball; do not decrease size of array; be sure that there are no gaps between elements of the array; throw exception if collection is empty
        void remove_this_item(const Stress_ball& sb); //remove a stress ball with a specific color and size from the collection; do not decrease size of array; be sure that there are no gaps between elements of the array; throw exception if collection is empty
        void make_empty(); //make collection empty (deallocate allocated memory, set to zero size and capacity)
        bool is_empty() const; //check if collection is empty; return true if is empty
        int total_items() const; //return total number of stress balls in collection
        int total_items(Stress_ball_sizes s) const; //return number of stress balls of the same size in the collection
        int total_items(Stress_ball_colors t) const; //return number of stress balls of the same color in the collection
        void print_items() const; //print all stress balls in collection
        Stress_ball& operator[](int i); //overloaded operator: directly access a stress ball in a collection in array at position i
        const Stress_ball& operator[](int i) const; //overloaded operator: directly access a stress ball in a const collection in array at position i
    private:
        Stress_ball *array; //pointer to dynamically allocated memory
        int size; //logical size of array = the number of elements in use
        int capacity; //physical size of array = the number of allocated elements
        void resize()
        {
            capacity *= 2;
            if(capacity == 0)
            {
                capacity = 2;
            }
            Stress_ball* new_array = new Stress_ball[capacity];
            for(int i = 0; i < size; i++)
            {
                new_array[i] = array[i];
            }
            delete[] array;
            array = new_array;
        }
        //Note that size <= capacity
};

istream& operator>>(istream& is, Collection& c);
ostream& operator <<(ostream& os, const Collection& c);
Collection make_union(const Collection& c1, const Collection& c2);
void swap(Collection& c1, Collection& c2);
void sort_by_size(Collection& c, Sort_choice sort);
Stress_ball_colors convertColor(const string &str);
Stress_ball_sizes convertSize(const string &str);

#endif