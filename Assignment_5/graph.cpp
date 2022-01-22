#include "graph.h"
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>

ostream& operator<<(ostream& o, const Vertex& ver)
{
    o << ver.label;
    return o;
};

Graph::~Graph()
{
    for(int i = 0; i < adj_list.size(); i++)
    {
        delete adj_list[i];
    }
}

void Graph::buildGraph(ifstream &input)
{
    int num;
    string line;
    vector<int> numbers;
    while(getline(input, line)) //seperates the string by spaces
    {
        stringstream ss(line);
        while(ss >> num)
        {
            numbers.push_back(num);
        }
        
        //Node List
        num = numbers[0];
        Vertex node(num);
        node_list.push_back(node);

        //Adj List
        list<int>* lst;
        lst = new list<int>;
        for(int i = 1; i < numbers.size()-1; i++)
        {
            num = numbers[i];
            lst->push_back(num);
            //cout << num << " ";
        }
        adj_list.push_back(lst);
        //cout << endl;
        numbers.clear();
    }
    input.close();
}

void Graph::displayGraph()
{
    for(int i = 0; i < node_list.size(); i++)
    {
        Vertex node = node_list[i];
        cout << node << ":";
        list<int>* lst;
        lst = new list<int>;
        lst = adj_list[i];
        for(auto itr = lst->begin(); itr != lst->end(); itr++)
        {
            cout << *itr << " ";
        }
        cout << endl;
    }
}