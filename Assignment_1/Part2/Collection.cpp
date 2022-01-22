#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <exception>
#include "Stress_ball.h"
#include "Collection.h"
using namespace std;

Collection::Collection()
{
    this->size = 0;
    this->capacity = 0;
    this->array = nullptr;
}

Collection::Collection(int s)
{
    this->size = 0;
    this->capacity = s;
    this->array = new Stress_ball[s];
}

Collection::Collection(const Collection &c)
{
    this->size = c.size;
    this->capacity = c.capacity;
    this->array = new Stress_ball[c.capacity];
    
    for(int i = 0; i < this->size; i++)
    {
        array[i] = c.array[i];
    }
}

Collection& Collection::operator=(const Collection &c)
{
    if(this != &c)
    {
        Stress_ball* other = new Stress_ball[c.size];
        for(int i = 0; i < c.size; i++)
        {
            Stress_ball test;
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

Collection::~Collection()
{
    if(!this->is_empty())
    {
        this->make_empty();
    }
}

Collection::Collection(Collection&& c)
{
    this->size = c.size;
    this->capacity = c.capacity;
    this->array = c.array;
    c.array = nullptr;
    c.capacity = 0;
    c.size = 0;
}

Collection& Collection::operator=(Collection&& c)
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

void Collection::insert_item(const Stress_ball& sb)
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

bool Collection::contains(const Stress_ball& sb) const
{
    for(int i = 0; i < this->size; i++)
    {
        Stress_ball test;
        test = array[i];
        if(sb == test)
        {
            return true;
        }
    }
    return false;
}

Stress_ball Collection::remove_any_item()
{
    if(this->is_empty() == false)
    {
        srand(time(NULL));
        int i;
        i = rand() % (this->size);
        Stress_ball test;
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

void Collection::remove_this_item(const Stress_ball& sb)
{
    if(this->is_empty() == false)
    {
        for(int i = 0; i < this->size; i++)
        {
            Stress_ball test;
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

void Collection::make_empty()
{
    if(this->array != nullptr)
    {
        delete[] array;
        this->array = nullptr;
    }
    this->size = 0;
    this->capacity = 0;
}

bool Collection::is_empty() const
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

int Collection::total_items() const
{
    return this->size;
}

int Collection::total_items(Stress_ball_sizes s) const
{
    int num;
    num = 0;
    for(int i = 0; i < this->size; i++)
    {
        Stress_ball test;
        test = array[i];
        if(test.get_size() == s)
        {
            num += 1;
        }
    }
    return num;
}

int Collection::total_items(Stress_ball_colors t) const
{
    int num;
    num = 0;
    for(int i = 0; i < this->size; i++)
    {
        Stress_ball test;
        test = array[i];
        if(test.get_color() == t)
        {
            num += 1;
        }
    }
    return num;
}

void Collection::print_items() const
{
    for(int i = 0; i < this->size; i++)
    {
        Stress_ball test;
        test = array[i];
        cout << test << endl;
    }
}

Stress_ball& Collection::operator[](int i)
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

const Stress_ball& Collection::operator[](int i) const
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

istream& operator>>(istream& is, Collection& c)
{
    string line;
    string colorStr;
    string sizeStr;
    Stress_ball_colors color;
    Stress_ball_sizes size;
    
    while(is >> colorStr >> sizeStr)
    {
        color = convertColor(colorStr);
        size = convertSize(sizeStr);
        Stress_ball test(color, size);
        c.insert_item(test);
    }

    return is;
}

ostream& operator<<(ostream& os, const Collection& c)
{
    for(int i = 0; i < c.total_items(); i++)
    {
        Stress_ball test;
        test = c[i];
        os << test << endl;
    }

    return os;
}

Collection make_union(const Collection& c1, const Collection& c2)
{
    int size;
    size = c1.total_items() + c2.total_items();
    Collection c3(size);
    for(int i = 0; i < c1.total_items(); i++)
    {
        Stress_ball test1;
        test1 = c1[i];
        c3.insert_item(test1);
    }
    for(int i = 0; i < c2.total_items(); i++)
    {
        Stress_ball test2;
        test2 = c2[i];
        c3.insert_item(test2);
    }
    return c3;
}

void swap(Collection& c1, Collection& c2)
{
    Collection temp(move(c1));
    c1 = move(c2);
    c2 = move(temp);
}

void sort_by_size(Collection&c, Sort_choice sort)
{
    Stress_ball temp;
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

Stress_ball_colors convertColor(const string &str)
{
    if(str == "red")
    {
        return red;
    }
    else if(str == "blue")
    {
        return blue;
    }
    else if(str == "yellow")
    {
        return yellow;
    }
    else
    {
        return green;
    }   
}

Stress_ball_sizes convertSize(const string &str)
{
    if(str == "small")
    {
        return small;
    }
    else if(str == "medium")
    {
        return medium;
    }
    else
    {
        return large;
    }
}