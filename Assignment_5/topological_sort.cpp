// topological sort

#include <iostream>
#include <list>
#include <queue>
#include <stdexcept>
#include "graph.h"

void Graph::compute_indegree()
{
  /*for(Vertex node : node_list)
  {
    for(int j = 0; j < node_list.size(); j++)
    {
      for(auto itr = adj_list[j]->begin(); itr != adj_list[j]->end(); itr++)
      {
        if(*itr == node.label)
        {
          node.indegree++;
        }
      }
    }
    cout << node << endl;
  }*/

  for(Vertex& node : node_list)
  {
    node.indegree = 0;
  }

  for(Vertex& node : node_list)
  {
    for(auto itr = adj_list[node.label - 1]->begin(); itr != adj_list[node.label - 1]->end(); itr++)
    {
      node_list[*itr - 1].indegree++;
    }
  }
}

void Graph::topological_sort()
{
  queue<int> q;
  int count = 0;
  int num;

  for(int i = 0; i < node_list.size(); i++)
  {
    if(node_list[i].indegree == 0)
    {
      q.push(i);
    }
  }

  while(!q.empty())
  {
    num = q.front();
    node_list[num].top_num = ++count;
    q.pop();
    top_order.push_back(node_list[num].label);
    list<int>* lst;
    lst = adj_list[num];
    for(auto itr = lst->begin(); itr != lst->end(); itr++)
    {
      num = *itr;
      if(--node_list[num - 1].indegree == 0)
      {
        q.push(num - 1);
      }
    }
  }

  if(count != node_list.size())
  {
    throw CycleFoundException("Cycle Found in Graph");
  }
}

void Graph::print_top_sort()
{
  for(int i = 0; i < top_order.size(); i++)
  {
    cout << top_order[i] << " ";
  }
}
