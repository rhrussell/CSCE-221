#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "Jeans.h"
#include "Collection.h"
using namespace std;

using CollectionJN = Collection<Jeans, Jeans_colors, Jeans_sizes>;

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

int main()
{
    fstream file1;
    fstream file2;
    CollectionJN c1;
    CollectionJN c2;
    
    file1.open("jeans1.data");
    file1 >> c1;
    file1.close();
    file2.open("jeans2.data");
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