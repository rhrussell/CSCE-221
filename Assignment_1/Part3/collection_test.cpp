#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "Stress_ball.h"
#include "Jeans.h"
#include "Collection.h"
using namespace std;

using CollectionSB = Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes>;
using CollectionJN = Collection<Jeans, Jeans_colors, Jeans_sizes>;

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

Jeans_colors convertJeansColor(const string &str)
{
    if(str == "white")
    {
        return Jeans_colors::white;
    }
    else if(str == "blue")
    {
        return Jeans_colors::blue;
    }
    else if(str == "brown")
    {
        return Jeans_colors::brown;
    }
    else
    {
        return Jeans_colors::black;
    }
}
  
Jeans_sizes convertJeansSize(const string &str)
{
    if(str == "small")
    {
        return Jeans_sizes::small;
    }
    else if(str == "medium")
    {
        return Jeans_sizes::medium;
    }
    else if(str == "large")
    {
        return Jeans_sizes::large;
    }
    else
    {
        return Jeans_sizes::xlarge;
    }
}

istream& operator>>(istream& is, CollectionJN& c)
{
    string line;
    string colorStr;
    string sizeStr;
    
    while(is >> colorStr >> sizeStr)
    {
        Jeans_colors color = convertJeansColor(colorStr);
        Jeans_sizes size = convertJeansSize(sizeStr);
        Jeans test(color, size);
        c.insert_item(test);
    }

    return is;
}

void test_stress_balls()
{
    fstream fileStressBall1;
    fstream fileStressBall2;
    CollectionSB c1;
    CollectionSB c2;

    fileStressBall1.open("stress_ball1.data");
    fileStressBall1 >> c1;
    fileStressBall1.close();
    fileStressBall2.open("stress_ball2.data");
    fileStressBall2 >> c2;
    fileStressBall2.close();

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

void test_jeans()
{
    fstream fileJean1;
    fstream fileJean2;
    CollectionJN c1;
    CollectionJN c2;
    
    fileJean1.open("jeans1.data");
    fileJean1 >> c1;
    fileJean1.close();
    fileJean2.open("jeans2.data");
    fileJean2 >> c2;
    fileJean2.close();

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
    cout << "How many Black Jeans are there in the first Collection? " << c1.total_items(Jeans_colors::black) << endl;
    cout << endl;
    cout << "How many Jeans are there in the first Collection? " << c1.total_items() << endl;
    cout << endl;
    cout << "How many White Jeans are there in the second Collection? " << c2.total_items(Jeans_colors::white) << endl;
    cout << endl;
    cout << "How many Jeans are there in the second Collection? " << c2.total_items() << endl;
    cout << endl;
    CollectionJN c3;
    c3 = make_union(c1, c2);
    cout << "Collection Three Before Sort: " << endl;
    c3.print_items();
    cout << endl;
    sort_by_size(c3, Sort_choice::selection_sort);
    cout << "Collection Three After Sort: " << endl;
    c3.print_items();
    cout << endl;
    cout << "How many White Jeans are there in the third Collection? " << c3.total_items(Jeans_colors::white) << endl;
    cout << "How many Blue Jeans are there in the third Collection? " << c3.total_items(Jeans_colors::blue) << endl;
    cout << "How many Brown Jeans are there in the third Collection? " << c3.total_items(Jeans_colors::brown) << endl;
    cout << "How many Black Jeans are there in the third Collection? " << c3.total_items(Jeans_colors::black) << endl;
    cout << "How many Small Jeans are there in the third Collection? " << c3.total_items(Jeans_sizes::small) << endl;
    cout << "How many Medium Jeans are there in the third Collection? " << c3.total_items(Jeans_sizes::medium) << endl;
    cout << "How many Large Jeans are there in the third Collection? " << c3.total_items(Jeans_sizes::large) << endl;
    cout << "How many XLarge Jeans are there in the third Collection? " << c3.total_items(Jeans_sizes::xlarge) << endl;
    cout << endl;
    cout << "How many Jeans are there in the third Collection? " << c3.total_items() << endl;
    cout << endl;
    swap(c1, c2);
    cout << "Collection One After Swap: " << endl;
    c1.print_items();
    cout << endl;
    cout << "Collection Two After Swap: " << endl;
    c2.print_items();
    cout << endl;
    CollectionJN c4 = make_copy(c3);
    cout << "Just Created a copy of Collection Three using make_copy()" << endl;
    cout << endl;
    cout << "Collection Four: " << endl;
    c4.print_items();
}

int main()
{
    int answer;
    cout << "What version to test: stress_ball (=0) or jeans (=1): ";
    cin >> answer;
    if (answer == 0)
    {
        test_stress_balls();
    }
    else if (answer == 1)
    {
        test_jeans();
    }
    else
    {
        cout << "Wrong value: " << answer << endl;
    }
}