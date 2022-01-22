// main function

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include "graph.h"

using namespace std;

int main(int argc, const char * argv[])
{
  if ( argc != 2 ) {
    cout << "usage: " << argv[0] << " input filename\n";
    exit(1);
  }

  string input_name = argv[1];
  ifstream input(input_name);
  if (!input) {
    cout << "Wrong or nonexisting input file\n";
    exit(1);
  }

  try
  {
    Graph graph;
    graph.buildGraph(input);
    cout << "Graph:" << endl;
    graph.displayGraph();
    cout << endl;
    cout << "Topological Sort: ";
    graph.compute_indegree(); // Part 2
    graph.topological_sort(); // Part 2
    graph.print_top_sort();   // Part 2
  }
  catch(CycleFoundException& e)
  {
    std::cerr << e.what() << endl;
  } 
  return 0;
}
