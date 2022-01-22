
#include <iostream>
#include <fstream>
#include "BSTree.h"

BSTree read_file(string file_name)
{
  /*
    open the file and use the input operator (operator>>)
    to construct a new tree
  */
    
  BSTree new_tree;
  ifstream infile;
  infile.open(file_name);
  // use >> to read in to new_tree
  infile >> new_tree;
  infile.close();
  return new_tree;
}


int main()
{
  // test the copy constructor
  cout << "Copy Constructor Test" << endl;
  BSTree bst;
  bst.insert(5);
  bst.insert(3);
  bst.insert(9);
  bst.insert(7);
  bst.insert(10);
  bst.insert(11);
  bst.update_search_times();
  cout << "Binary Search Tree One (Original): " << endl;
  cout << bst << endl;
  bst.inorder(cout);
  cout << endl;
  cout << bst.get_average_search_time() << endl;
  cout << endl << endl;

  BSTree bst2(bst);
  bst2.update_search_times();
  cout << "Binary Search Tree Two (Copy Constructor): " << endl;
  //cout << bst << endl;
  cout << bst2 << endl;
  bst2.inorder(cout);
  cout << endl;
  cout << bst2.get_average_search_time() << endl;
  cout << endl << endl;

  // test the copy assignment
  cout << "Copy Assignment Test" << endl;
  BSTree bst3;
  bst3 = bst2;
  bst3.update_search_times();
  cout << "Binary Search Tree Three (Copy Assignment): " << endl;
  //cout << bst2 << endl;
  cout << bst3 << endl;
  bst3.inorder(cout);
  cout << endl;
  cout << bst3.get_average_search_time() << endl;
  cout << endl << endl;

  // test the move constructor
  cout << "Move Constructor Test" << endl;
  cout << "Binary Search Tree (Original): " << endl;
  cout << bst2 << endl;
  bst2.inorder(cout);
  cout << endl;
  cout << bst2.get_average_search_time() << endl;
  cout << endl;
  BSTree bst4 = move(bst2);
  cout << "Binary Search Tree (Original After Move): " << endl;
  cout << bst2 << endl;
  cout << "Binary Search Tree Four (Move Constructor): " << endl;
  cout << bst4 << endl;
  bst4.inorder(cout);
  cout << endl;
  cout << bst4.get_average_search_time() << endl;
  cout << endl << endl;

  // test the move assignment
  cout << "Move Assignment Test" << endl;
  cout << "Binary Search Tree (Original): " << endl;
  bst.update_search_times();
  cout << bst << endl;
  bst.inorder(cout);
  cout << endl;
  cout << bst.get_average_search_time() << endl;
  BSTree bst5;
  bst5 = move(bst);
  bst5.update_search_times();
  cout << endl;
  cout << "Binary Search Tree (Original After Move): " << endl;
  cout << bst << endl;
  cout << "Binary Searh Tree Five (Move Assignment): " << endl;
  cout << bst5 << endl;
  bst5.inorder(cout);
  cout << endl;
  cout << bst5.get_average_search_time() << endl;
  cout << endl << endl;
  
  ofstream file;

  for(int i = 1; i <= 12; i++) 
  {
    string dir= "data-files/"+std::to_string(i);
    BSTree l = read_file(dir+"l");
    l.update_search_times();
    if(l.get_size() < 16)
    {
      //cout << "In-order Traversal: ";
      l.inorder(cout);
      cout << endl;
      cout << l << endl;
      string newdir = "new-files/" + std::to_string(i);
      newdir += "l";
      file.open(newdir);
      //file << l.inorder(cout);
      l.inorder(file);
      file.close();
    }
    else
    {
      string newdir = "new-files/" + std::to_string(i);
      newdir += "l";
      file.open(newdir);
      //file << l.inorder(cout);
      l.inorder(file);
      file.close();
    }
    cout << "average search time linear " << i << " " << l.get_average_search_time() << endl;
    cout << "number of nodes linear " << l.get_size() << endl;
    BSTree p = read_file(dir+"p");
    p.update_search_times();
    if(p.get_size() < 16)
    {
      //cout << "In-order Traversal: ";
      p.inorder(cout);
      cout << endl;
      cout << p << endl;
      string newdir = "new-files/" + std::to_string(i);
      newdir += "p";
      file.open(newdir);
      //file << p.inorder(cout);
      p.inorder(file);
      file.close();
    }
    else
    {
      string newdir = "new-files/" + std::to_string(i);
      newdir += "p";
      file.open(newdir);
      //file << p.inorder(cout);
      p.inorder(file);
      file.close();
    }
    cout << "average search time perfect "<< i << " " << p.get_average_search_time() << endl;
    cout << "number of nodes perfect " << p.get_size() << endl;
    BSTree r = read_file(dir+"r");
    r.update_search_times();
    if(r.get_size() < 16)
    {
      //cout << "In-order Traversal: ";
      r.inorder(cout);
      cout << endl;
      cout << r << endl;
      string newdir = "new-files/" + std::to_string(i);
      newdir += "r";
      file.open(newdir);
      //file << r.inorder(cout);
      r.inorder(file);
      file.close();
    }
    else
    {
      string newdir = "new-files/" + std::to_string(i);
      newdir += "r";
      file.open(newdir);
      //file << r.inorder(cout);
      r.inorder(file);
      file.close();
    }
    cout << "average search time random "<< i << " " << r.get_average_search_time() << endl;
    cout << "number of nodes random " << r.get_size() << endl;
    if(i <= 4) 
    {
      p.update_search_times();
      cout << "perfect tree " << i << endl << p;
    }

    cout << endl;
  }
}

