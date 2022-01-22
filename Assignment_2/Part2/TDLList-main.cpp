// testing the templated class DLList

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

#include "TemplatedDLList.h"

using namespace std;

int main ()
{
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DLList<string> dll;
  cout << "list: " << dll << endl << endl;

  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10; i<=100; i+=10) {
    stringstream ss;
    ss << i;
    dll.insert_last(ss.str());
  }
  cout << "list: " << dll << endl << endl;

  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10; i<=100; i+=10) {
    stringstream ss;
    ss << i;
    dll.insert_first(ss.str());
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Copy to a new list" << endl;
  DLList<string> dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  cout << "Assign to another new list" << endl;
  DLList<string> dll3;
  dll3 = dll;
  cout << "list3: " << dll3 << endl << endl;
  
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0; i<10; i++) {
    dll.remove_last();
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0; i<10; i++) {
    dll.remove_first();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;

  //Move Constructor
  DLList<string> dll4 = move(dll2);
  cout << "Move Constructor" << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list4: " << dll4 << endl;

  //Move Assignment
  DLList<string> dll5;
  dll5 = move(dll3);
  cout << "Move Assignment" << endl;
  cout << "list3: " << dll3 << endl;
  cout << "list5: " << dll5 << endl;

  // more testing...
  // add tests for insert_after, insert_before
  DLListNode<string> *node = dll4.first_node();
  node = node->next->next->next; //70
  stringstream ss1;
  ss1 << 75;
  dll4.insert_before(*node, ss1.str());
  cout << "Insert Before: " << endl;
  cout << "list4: " << dll4 << endl;
  node = node->prev->prev;
  stringstream ss2;
  ss2 << 76;
  dll4.insert_after(*node, ss2.str());
  cout << "Insert After: " << endl;
  cout << "list4: " << dll4 << endl;

  // add tests for remove_after, remove_before
  node = dll4.first_node();
  node = node->next->next->next->next->next; //70
  dll4.remove_before(*node);
  cout << "Remove Before: " << endl;
  cout << "list4: " << dll4 << endl;
  node = node->prev->prev; //80
  dll4.remove_after(*node);
  cout << "Remove After: " << endl;
  cout << "list4: " << dll4 << endl;
  
  return 0;
}
