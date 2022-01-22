// test of the DLList class

#include <iostream>
#include <cstdlib>
#include "DLList.h"

using namespace std;

int main ()
{
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DLList dll;
  cout << "list: " << dll << endl << endl;
  
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10; i <= 100; i+=10) {
    dll.insert_last(i);
  }
  cout << "list: " << dll << endl << endl;

  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10; i <= 100; i+=10) {
    dll.insert_first(i);
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Copy to a new list" << endl;
  DLList dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  cout << "Assign to another new list" << endl;
  DLList dll3;
  dll3 = dll;
  cout << "list3: " << dll3 << endl << endl;
  
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0; i < 10; i++) {
    dll.remove_last();
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0; i < 10; i++) {
    dll.remove_first();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;

  //Move Constructor
  DLList dll4 = move(dll2);
  cout << "Move Constructor" << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list4: " << dll4 << endl;

  //Move Assignment
  DLList dll5;
  dll5 = move(dll3);
  cout << "Move Assignment" << endl;
  cout << "list3: " << dll3 << endl;
  cout << "list5: " << dll5 << endl;

  // more testing...
  // add tests for insert_after, insert_before
  DLListNode *node = dll4.first_node();
  node = node->next->next->next; //70
  dll4.insert_before(*node, 75);
  cout << "Insert Before: " << endl;
  cout << "list4: " << dll4 << endl;
  node = node->prev->prev;
  dll4.insert_after(*node, 76);
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
