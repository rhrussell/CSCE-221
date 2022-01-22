//#ifndef BSTREE_H
//#define BSTREE_H
#include<iostream>
#include<vector>
#include<algorithm>
#include "BSTree.h"

// input / output operators
ostream& operator<<(ostream& out, BSTree& tree)
{
  tree.print_level_by_level(out);
  return out;
}

ostream& operator<<(ostream& out, Node node)
{
  return out << "( " << node.value << ", "
	     << node.search_time << " )";
}

istream& operator>>(istream& in, BSTree& tree)
{
  /*
    take input from the in stream, and build your tree
    input will look like
    4 
    2 
    6 
    1 
    3 
    5 
    7
  */
  int next;
  while(in >> next) 
    tree.insert(next);
  return in;
}

///////////// Implementation To Do ////////////////////

// copy constructor
BSTree::BSTree(const BSTree& other)
{
  /*
    complete this copy constructor
    make sure when copying nodes to copy
    the value and left and right children
  */
  this->root = nullptr;
  copy_helper(other.root);
}

// move constructor
BSTree::BSTree(BSTree&& other)
{
  this->root = other.root;
  this->size = other.size;
  other.root = nullptr;
  other.size = 0;
}

//copy assignment
BSTree& BSTree::operator=(const BSTree& other)
{
  /*
    complete this assignment operator
    make sure when copying nodes to copy
    the value
    and left and right children
    not important for this part but will be used later
  */
 if(this != &other)
 {
   this->root = nullptr;
   copy_helper(other.root);
 }

 return *this;
}

// move assignment
BSTree& BSTree::operator=(BSTree&& other)
{
  if(this != &other)
  {
    delete_tree(root);
    copy_helper(other.root);
    this->root = other.root;
    this->size = other.size;
    other.root = nullptr;
    other.size = 0;
  }

  return *this;
}

// destructor
BSTree::~BSTree()
{
  // use a helper function
  delete_tree(this->root);
  root = nullptr;
}

// recursive
void BSTree::copy_helper(Node* root)
{
  if(root)
  {
    insert(root->value);
    copy_helper(root->left);
    copy_helper(root->right);
  }
}

Node* BSTree::search_helper(Node* root, int obj)
{
  if(root == nullptr || root->value == obj)
  {
    return root;
  }
  if(root->value < obj)
  {
    return search_helper(root->right, obj);
  }
  
  return search_helper(root->left, obj);
}

Node* BSTree::insert_helper(Node* root, int obj)
{
  if(root == nullptr)
  {
    //Node *temp = new Node(obj, nullptr, nullptr);
    Node *temp = new Node();
    temp->value = obj;
    temp->left = temp->right = nullptr;
    return temp;
  }
  else if(obj <= root->value)
  {
    root->left = insert_helper(root->left, obj);
  }
  else if(obj > root->value)
  {
    root->right = insert_helper(root->right, obj);
  }

  return root;
}

void BSTree::delete_tree(Node* root)
{
  if(root == nullptr)
  {
    return;
  }
  if(root->left != nullptr)
  {
    delete_tree(root->left);
  }
  if(root->right != nullptr)
  {
    delete_tree(root->right);
  }

  delete root;
}

Node* BSTree::insert(int obj)
{
  /*
    insert a node into the tree
    first find where the node should go
    then modify pointers to connect your new node 
  */
 size++;
 this->root = insert_helper(this->root, obj);
 return this->root;
}

Node* BSTree::search(int obj)
{
  /*
    recursivly search down the tree to find the node that contains obj
    if you dont find anything return null
  */
 return search_helper(this->root, obj);
}

void BSTree::update_search_times_helper(Node* root, int num)
{
  if(root != nullptr)
  {
    root->search_time = num;
    update_search_times_helper(root->left, num + 1);
    update_search_times_helper(root->right, num + 1);
  }
}

void BSTree::update_search_times()
{
  /*
    do a BFS or DFS of your tree and update the searchtimes of all nodes
  */
 update_search_times_helper(this->root, 1);
}


ostream& BSTree::inorder(ostream& out)
{
  /*
    print your nodes in infix order
    if our tree looks like 

    4
    2 6
    1 3 5 7

    we should get

    1 2 3 4 5 6 7 
  */

 inorder_helper(this->root, out);
}

ostream& BSTree::inorder_helper(Node* root, ostream& out)
{
  if(root == nullptr)
  {
    return out;
  }
  inorder_helper(root->left, out);
  pretty_print_node(out, root);
  inorder_helper(root->right, out);
}

// implemented
void BSTree::pretty_print_node(ostream& out,Node* node)
{
  out << node->value << "["<<node->search_time<<"] ";
}

// implemented
ostream& BSTree::print_level_by_level(ostream& out)
{
  /*
    print the tree using a BFS 
    output should look like this if we dont have a full tree

    4
    2 6
    1 X 5 7
    X X X X X X X 9

    it will be helpfull to do this part iterativly, 
    so do the BFS with the std stack data structure.

    it may also be helpfull to put the entire tree into a vector 
    (probably google this if you dont know how to do it)
  */

  if(root == nullptr)
    return out;

  bool hasNodes = true;
  vector<Node*> current_level;
  vector<Node*> next_level;
  current_level.push_back(root);
  while(hasNodes) {
    hasNodes = false;
    for(auto node : current_level) {
      if(node != nullptr) {
	pretty_print_node(out, node);
	if(node->left != nullptr)
	  hasNodes = true;
	if(node->right != nullptr)
	  hasNodes = true;
	
	next_level.push_back(node->left);
	next_level.push_back(node->right);
      } else {
	out << "X ";
	next_level.push_back(nullptr);
	next_level.push_back(nullptr);
      }
    }
    out << endl;
    current_level.clear();
    current_level = next_level;
    next_level.clear();
  }

  return out;
}

// implemented
int BSTree::get_total_search_time(Node* node)
{
  if(node == nullptr)
    return 0;

  return get_total_search_time(node->left) +
    get_total_search_time(node->right) + node->search_time;
}

// implemented
float BSTree::get_average_search_time()
{
  int total_search_time = get_total_search_time(root);
  if(total_search_time == 0)
    return -1;
	
  return ((float)total_search_time)/size;
}
