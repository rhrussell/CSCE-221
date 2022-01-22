#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <exception>
using namespace std;

#ifndef Collection_H
#define Collection_H

enum class Sort_choice {bubble_sort, insertion_sort, selection_sort};
template <typename Obj, typename F1, typename F2>

struct Collection
{
    public:
        Collection(); //default constructor: Default size of collection is 8
        Collection(int s); //constructor with one arugment which is the required of the collection
        Collection(const Collection &c); //copy constructor: makes a copy of a collection
        Collection<Obj, F1, F2>& operator=(const Collection<Obj, F1, F2> &c); //copy assignment: overwrites an existing collection by another collection
        ~Collection(); //destructor: destroys a collection(deallocates allocated memeory, set to zero size and capacity)
        Collection(Collection<Obj, F1, F2>&& c); //move constructor: efficiently creates a new collection from an existing one
        Collection<Obj, F1, F2>& operator=(Collection<Obj, F1, F2>&& c); //move assignment: efficiently copies a collection during an assignment
        void insert_item(const Obj& c); //insert stress ball to collection; if collection = full, double array size; use resize()
        bool contains(const Obj& c) const; //checks if a stress ball with a certain color or size is in the collection; returns true if it is
        Obj remove_any_item(); //remove and return a random stress ball; do not decrease size of array; be sure that there are no gaps between elements of the array; throw exception if collection is empty
        void remove_this_item(const Obj& c); //remove a stress ball with a specific color and size from the collection; do not decrease size of array; be sure that there are no gaps between elements of the array; throw exception if collection is empty
        void make_empty(); //make collection empty (deallocate allocated memory, set to zero size and capacity)
        bool is_empty() const; //check if collection is empty; return true if is empty
        int total_items() const; //return total number of stress balls in collection
        int total_items(F1 colors) const; //return number of stress balls of the same color in the collection
        int total_items(F2 sizes) const; //return number of stress balls of the same size in the collection
        void print_items() const; //print all stress balls in collection
        Obj& operator[](int i); //overloaded operator: directly access a stress ball in a collection in array at position i
        const Obj& operator[](int i) const; //overloaded operator: directly access a stress ball in a const collection in array at position i
    private:
        Obj *array; //pointer to dynamically allocated memory
        int size; //logical size of array = the number of elements in use
        int capacity; //physical size of array = the number of allocated elements
        void resize()
        {
            capacity *= 2;
            if(capacity == 0)
            {
                capacity = 2;
            }
            Obj *new_array = new Obj[capacity];
            for(int i = 0; i < size; i++)
            {
                new_array[i] = array[i];
            }
            delete[] array;
            array = new_array;
        }
        //Note that size <= capacity
};

template <typename Obj, typename F1, typename F2>
ostream& operator <<(ostream& os, const Collection<Obj, F1, F2>& c);
template <typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2> make_union(const Collection<Obj, F1, F2>& c1, const Collection<Obj, F1, F2>& c2);
template <typename Obj, typename F1, typename F2>
void swap(Collection<Obj, F1, F2>& c1, Collection<Obj, F1, F2>& c2);
template <typename Obj, typename F1, typename F2>
void sort_by_size(Collection<Obj, F1, F2>& c, Sort_choice sort);
template <typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2> make_copy(Collection<Obj, F1, F2>& c2);

#endif

template <typename Obj, typename F1, typename F2> 
Collection<Obj, F1, F2>::Collection()
{
    this->size = 0;
    this->capacity = 0;
    this->array = nullptr;
}

template <typename Obj, typename F1, typename F2> 
Collection<Obj, F1, F2>::Collection(int s)
{
    this->size = 0;
    this->capacity = s;
    this->array = new Obj[s];
}

template <typename Obj, typename F1, typename F2> 
Collection<Obj, F1, F2>::Collection(const Collection<Obj, F1, F2> &c)
{
    this->size = c.size;
    this->capacity = c.capacity;
    this->array = new Obj[c.capacity];
    
    for(int i = 0; i < this->size; i++)
    {
        array[i] = c.array[i];
    }
}

template <typename Obj, typename F1, typename F2> 
Collection<Obj, F1, F2>& Collection<Obj, F1, F2>::operator=(const Collection<Obj, F1, F2> &c)
{
    if(this != &c)
    {
        Obj* other = new Obj[c.size];
        for(int i = 0; i < c.size; i++)
        {
            Obj test;
            test = c.array[i];
            other[i] = test;
        }
        delete[] array;
        this->size = c.size;
        this->capacity = c.capacity;
        this->array = other;
        return *this;
    }
}

template <typename Obj, typename F1, typename F2> 
Collection<Obj, F1, F2>::~Collection()
{
    if(!this->is_empty())
    {
        this->make_empty();
    }
}

template <typename Obj, typename F1, typename F2> 
Collection<Obj, F1, F2>::Collection(Collection&& c)
{
    this->size = c.size;
    this->capacity = c.capacity;
    this->array = c.array;
    c.array = nullptr;
    c.capacity = 0;
    c.size = 0;
}

template <typename Obj, typename F1, typename F2> 
Collection<Obj, F1, F2>& Collection<Obj, F1, F2>::operator=(Collection<Obj, F1, F2>&& c)
{
    if(this != &c)
    {
        this->make_empty();
        this->size = c.size;
        this->capacity = c.capacity;
        this->array = c.array;
        c.array = nullptr;
        c.capacity = 0;
        c.size = 0;
    }
}

template <typename Obj, typename F1, typename F2> 
void Collection<Obj, F1, F2>::insert_item(const Obj& sb)
{
    if(this->size == this->capacity)
    {
        resize();
        array[this->size] = sb;
        this->size++;
    }
    else
    {
        array[this->size] = sb;
        this->size++;
    }   
}

template <typename Obj, typename F1, typename F2> 
bool Collection<Obj, F1, F2>::contains(const Obj& sb) const
{
    for(int i = 0; i < this->size; i++)
    {
        Obj test;
        test = array[i];
        if(sb == test)
        {
            return true;
        }
    }
    return false;
}

template <typename Obj, typename F1, typename F2> 
Obj Collection<Obj, F1, F2>::remove_any_item()
{
    if(this->is_empty() == false)
    {
        srand(time(NULL));
        int i;
        i = rand() % (this->size);
        Obj test;
        test = array[i];
        for(int j = i; j < this->size - 1; j++)
        {
            array[j] = array[j + 1];
        }
        this->size -= 1;
        return test;
    }
    else
    {
        throw "Collection is empty.";
    }
}

template <typename Obj, typename F1, typename F2> 
void Collection<Obj, F1, F2>::remove_this_item(const Obj& sb)
{
    if(this->is_empty() == false)
    {
        for(int i = 0; i < this->size; i++)
        {
            Obj test;
            test = array[i];
            if(sb == test)
            {
                for(int j = i; j < this->size - 1; j++)
                {
                    array[j] = array[j + 1];
                }
            }
            size -= 1;
        }
    }
    else
    {
        cout <<  "Collection is empty." << endl;
    }
}

template <typename Obj, typename F1, typename F2> 
void Collection<Obj, F1, F2>::make_empty()
{
    if(this->array != nullptr)
    {
        delete[] array;
        this->array = nullptr;
    }
    this->size = 0;
    this->capacity = 0;
}

template <typename Obj, typename F1, typename F2> 
bool Collection<Obj, F1, F2>::is_empty() const
{
    if(this->size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename Obj, typename F1, typename F2> 
int Collection<Obj, F1, F2>::total_items() const
{
    return this->size;
}

template <typename Obj, typename F1, typename F2> 
int Collection<Obj, F1, F2>::total_items(F1 t) const
{
    int num;
    num = 0;
    for(int i = 0; i < this->size; i++)
    {
        Obj test;
        test = array[i];
        if(test.get_color() == t)
        {
            num += 1;
        }
    }
    return num;
}

template <typename Obj, typename F1, typename F2> 
int Collection<Obj, F1, F2>::total_items(F2 s) const
{
    int num;
    num = 0;
    for(int i = 0; i < this->size; i++)
    {
        Obj test;
        test = array[i];
        if(test.get_size() == s)
        {
            num += 1;
        }
    }
    return num;
}

template <typename Obj, typename F1, typename F2> 
void Collection<Obj, F1, F2>::print_items() const
{
    for(int i = 0; i < this->size; i++)
    {
        Obj test;
        test = array[i];
        cout << test << endl;
    }
}

template <typename Obj, typename F1, typename F2> 
Obj& Collection<Obj, F1, F2>::operator[](int i)
{
    if(i < 0 || i > (this->size - 1))
    {
        throw "Array index out of bounds";
    }
    else
    {
        return array[i];
    }
}

template <typename Obj, typename F1, typename F2> const 
Obj& Collection<Obj, F1, F2>::operator[](int i) const
{
    if(i < 0 || i > (this->size - 1))
    {
        throw "Array index out of bound";
    }
    else
    {
        return array[i];
    }
}

template <typename Obj, typename F1, typename F2> 
ostream& operator<<(ostream& os, const Collection<Obj, F1, F2>& c)
{
    for(int i = 0; i < c.total_items(); i++)
    {
        Obj test;
        test = c[i];
        os << test << endl;
    }

    return os;
}

template <typename Obj, typename F1, typename F2> 
Collection<Obj, F1, F2> make_union(const Collection<Obj, F1, F2>& c1, const Collection<Obj, F1, F2>& c2)
{
    int size;
    size = c1.total_items() + c2.total_items();
    Collection<Obj, F1, F2> c3(size);
    for(int i = 0; i < c1.total_items(); i++)
    {
        Obj test1;
        test1 = c1[i];
        c3.insert_item(test1);
    }
    for(int i = 0; i < c2.total_items(); i++)
    {
        Obj test2;
        test2 = c2[i];
        c3.insert_item(test2);
    }
    return c3;
}

template <typename Obj, typename F1, typename F2>  
void swap(Collection<Obj, F1, F2>& c1, Collection<Obj, F1, F2>& c2)
{
    Collection<Obj, F1, F2> temp(move(c1));
    c1 = move(c2);
    c2 = move(temp);
}

template <typename Obj, typename F1, typename F2> 
void sort_by_size(Collection<Obj, F1, F2>&c, Sort_choice sort)
{
    Obj temp;
    int j;
    int min_index;
    switch(sort)
    {
        case Sort_choice::bubble_sort:
            for(int i = 0; i < c.total_items(); i++)
            {
                for(int j = 0; j < (c.total_items() - i - 1); j++)
                {
                    if(c[j].get_size() > c[j + 1].get_size())
                    {
                        temp = c[j + 1];
                        c[j + 1] = c[j];
                        c[j] = temp;
                    }
                }
            } 
        
        case Sort_choice::insertion_sort:
            for(int i = 1; i < c.total_items(); i++)
            {
                temp = c[i];
                j = i - 1;

                while(j >= 0 && c[j].get_size() > temp.get_size())
                {
                    c[j + 1] = c[j];
                    j -= 1;
                }
                c[j + 1] = temp;
            }

        case Sort_choice::selection_sort:
            for(int i = 0; i < (c.total_items() - 1); i++)
            {
                min_index = i;
                for(int j = i + 1; j < c.total_items(); j++)
                {
                    if(c[j].get_size() < c[min_index].get_size())
                    {
                        min_index = j;
                    }
                }

                temp = c[i];
                c[i] = c[min_index];
                c[min_index] = temp;
            }
    }
}

template <typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2> make_copy(Collection<Obj, F1, F2>& c2)
{
    return Collection<Obj, F1, F2>(c2);
}