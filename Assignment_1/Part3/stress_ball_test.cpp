#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "Stress_ball.h"
#include "Collection.h"
using namespace std;

using CollectionSB = Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes>;

Stress_ball_colors convertStressBallColor(const string &str)
{
    if(str == "red")
    {
        return Stress_ball_colors::red;
    }
    else if(str == "blue")
    {
        return Stress_ball_colors::blue;
    }
    else if(str == "yellow")
    {
        return Stress_ball_colors::yellow;
    }
    else
    {
        return Stress_ball_colors::green;
    }
}
  
Stress_ball_sizes convertStressBallSize(const string &str)
{
    if(str == "small")
    {
        return Stress_ball_sizes::small;
    }
    else if(str == "medium")
    {
        return Stress_ball_sizes::medium;
    }
    else
    {
        return Stress_ball_sizes::large;
    }
}

istream& operator>>(istream& is, CollectionSB& c)
{
    string line;
    string colorStr;
    string sizeStr;
    
    while(is >> colorStr >> sizeStr)
    {
        Stress_ball_colors color = convertStressBallColor(colorStr);
        Stress_ball_sizes size = convertStressBallSize(sizeStr);
        Stress_ball test(color, size);
        c.insert_item(test);
    }

    return is;
}

int main()
{
    fstream file1;
    fstream file2;
    CollectionSB c1;
    CollectionSB c2;

    file1.open("stress_ball1.data");
    file1 >> c1;
    file1.close();
    file2.open("stress_ball2.data");
    file2 >> c2;
    file2.close();

    cout << "Collection One Before Sort: " << endl;
    c1.print_items();
    cout << endl;
    cout << "Collection Two Before Sort: " << endl;
    c2.print_items();
    cout << endl;
    sort_by_size(c1, Sort_choice::bubble_sort);
    sort_by_size(c2, Sort_choice::insertion_sort);
    cout << "Collection One After Sort: " << endl;
    c1.print_items();
    cout << endl;
    cout << "Collection Two After Sort: " << endl;
    c2.print_items();
    cout << endl;
    cout << "How many Red Stress Balls are there in the first Collection? " << c1.total_items(Stress_ball_colors::red) << endl;
    cout << endl;
    cout << "How many Stress Balls are there in the first Collection? " << c1.total_items() << endl;
    cout << endl;
    cout << "How many Green Stress Balls are there in the second Collection? " << c2.total_items(Stress_ball_colors::green) << endl;
    cout << endl;
    cout << "How many Stress Balls are there in the second Collection? " << c2.total_items() << endl;
    cout << endl;
    CollectionSB c3;
    c3 = make_union(c1, c2);
    cout << "Collection Three Before Sort: " << endl;
    c3.print_items();
    cout << endl;
    sort_by_size(c3, Sort_choice::selection_sort);
    cout << "Collection Three After Sort: " << endl;
    c3.print_items();
    cout << endl;
    cout << "How many Red Stress Balls are there in the third Collection? " << c3.total_items(Stress_ball_colors::red) << endl;
    cout << "How many Blue Stress Balls are there in the third Collection? " << c3.total_items(Stress_ball_colors::blue) << endl;
    cout << "How many Yellow Stress Balls are there in the third Collection? " << c3.total_items(Stress_ball_colors::yellow) << endl;
    cout << "How many Green Stress Balls are there in the third Collection? " << c3.total_items(Stress_ball_colors::green) << endl;
    cout << "How many Small Stress Balls are there in the third Collection? " << c3.total_items(Stress_ball_sizes::small) << endl;
    cout << "How many Medium Stress Balls are there in the third Collection? " << c3.total_items(Stress_ball_sizes::medium) << endl;
    cout << "How many Large Stress Balls are there in the third Collection? " << c3.total_items(Stress_ball_sizes::large) << endl;
    cout << endl;
    cout << "How many Stress Balls are there in the third Collection? " << c3.total_items() << endl;
    cout << endl;
    swap(c1, c2);
    cout << "Collection One After Swap: " << endl;
    c1.print_items();
    cout << endl;
    cout << "Collection Two After Swap: " << endl;
    c2.print_items();
    cout << endl;
    CollectionSB c4 = make_copy(c3);
    cout << "Just Created a copy of Collection Three using make_copy()" << endl;
    cout << endl;
    cout << "Collection Four: " << endl;
    c4.print_items();
}
