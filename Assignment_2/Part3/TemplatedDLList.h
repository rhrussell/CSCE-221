// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

//class DLList; // class declaration
template <typename T> 
// doubly linked list node
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e = {}, DLListNode *p = nullptr, DLListNode *n = nullptr)
    : obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
  DLList() : header(T()), trailer(T()) // default constructor
  { header.next = &trailer; trailer.prev = &header; }
  DLList(const DLList<T>& dll); // copy constructor
  DLList(DLList<T>&& dll); // move constructor
  ~DLList(); // destructor
  DLList<T>& operator=(const DLList<T>& dll); // copy assignment operator
  DLList<T>& operator=(DLList<T>&& dll); // move assignment operator
  // return the pointer to the first node
  DLListNode<T> *first_node() const { return header.next; } 
  // return the pointer to the trailer
  const DLListNode<T> *after_last_node() const { return &trailer; }
  // return if the list is empty
  bool is_empty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insert_first(T obj); // insert to the first node
  T remove_first(); // remove the first node
  void insert_last(T obj); // insert to the last node
  T remove_last(); // remove the last node
  void insert_after(DLListNode<T> &p, T obj);
  void insert_before(DLListNode<T> &p, T obj);
  T remove_after(DLListNode<T> &p);
  T remove_before(DLListNode<T> &p);
};

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll);

#endif

// extend runtime_error from <stdexcept>
//template <typename T>
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};

// copy constructor
template <typename T>
DLList<T>::DLList(const DLList<T>& dll)
{
  header.next = &trailer;
  trailer.prev = &header;
  DLListNode<T> *temp = dll.header.next;
  while(temp != dll.trailer.prev)
  {
    this->insert_last(temp->obj);
    temp = temp->next;
  }
  this->insert_last(temp->obj);
}

// move constructor
template <typename T>
DLList<T>::DLList(DLList<T>&& dll)
{
  if(dll.is_empty())
  {
    header.next = &trailer;
    trailer.prev = &header;
  }
  else
  {
    header.next = dll.header.next;
    dll.header.next->prev = &header;
    trailer.prev = dll.trailer.prev;
    dll.trailer.prev->next = &trailer;
    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;
  }
}

// copy assignment operator
template <typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& dll)
{
  if(this != &dll)
  {
    DLListNode<T> *temp = this->header.next;
    while(temp != &trailer)
    {
      delete temp;
      temp = temp->next;
    }
  }

  header.next = &trailer;
  trailer.prev = &header;
  DLListNode<T> *node = dll.header.next;
  while(node != dll.trailer.prev)
  {
    this->insert_last(node->obj);
    node = node->next;
  }
  this->insert_last(node->obj);
}

// move assignment operator
template <typename T>
DLList<T>& DLList<T>::operator=(DLList<T>&& dll)
{
  if(dll.is_empty())
  {
    header.next = &trailer;
    trailer.prev = &header;
  }

  if(this != &dll)
  {
    DLListNode<T> *temp = this->header.next;
    while(temp != &trailer)
    {
      delete temp;
      temp = temp->next;
    }
    header.next = dll.header.next;
    dll.header.next->prev = &header;
    trailer.prev = dll.trailer.prev;
    dll.trailer.prev->next = &trailer;
    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;
  }
}

// destructor
template <typename T>
DLList<T>::~DLList()
{
  if(this->is_empty())
  {
    header.next = &trailer;
    trailer.prev = &header;
  }

  DLListNode<T> *prev_node;
  DLListNode<T> *node = header.next;

  while(node != &trailer)
  {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

// insert a new object as the first one
template <typename T>
void DLList<T>::insert_first(T obj)
{ 
  DLListNode<T> *newNode = new DLListNode<T>(obj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}

// insert a new object as the last one
template <typename T>
void DLList<T>::insert_last(T obj)
{
  DLListNode<T> *newNode = new DLListNode<T>(obj, trailer.prev, &trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

// remove the first node from the list
template <typename T>
T DLList<T>::remove_first()
{ 
  if(this->is_empty())
  {
    throw EmptyDLList("Empty Doubly Linked List");
  }
  DLListNode<T> *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  T obj = node->obj;
  delete node;
  return obj;
}

// remove the last node from the list
template <typename T>
T DLList<T>::remove_last()
{
  if(this->is_empty())
  {
    throw EmptyDLList("Empty Doubly Linked List");
  }
  DLListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}

// return the first object (do not remove)
template <typename T>
T DLList<T>::first() const
{ 
  if(this->is_empty())
  {
    throw EmptyDLList("Empty Doubly Linked List");
  }
  return header.next->obj;
}

// return the last object (do not remove)
template <typename T>
T DLList<T>::last() const
{
  if(this->is_empty())
  {
    throw EmptyDLList("Empty Doubly Linked List");
  }
  return trailer.prev->obj;
}

// insert a new node after the node p
template <typename T>
void DLList<T>::insert_after(DLListNode<T> &p, T obj)
{
  if(&p == &trailer)
  {
    throw "Cant insert after trailer node";
  }

  DLListNode<T> *node = new DLListNode<T>(obj, &p, p.next);
  node->prev->next = node;
  node->next->prev = node;
}

// insert a new node before the node p
template <typename T>
void DLList<T>::insert_before(DLListNode<T> &p, T obj)
{
  if(&p == &header)
  {
    throw "Cant insert before header node";
  }

  DLListNode<T> *node = new DLListNode<T>(obj, p.prev, &p);
  node->prev->next = node;
  node->next->prev = node;
}

// remove the node after the node p
template <typename T>
T DLList<T>::remove_after(DLListNode<T> &p)
{
  if(this->is_empty())
  {
    throw EmptyDLList("Empty Doubly Linked List");
  }
  if(&p == &trailer)
  {
    throw "Cant remove after trailer node";
  }
  if(&p == trailer.prev)
  {
    throw "Cant remove trailer node";
  }
  DLListNode<T> *node = header.next;
  while(node != &p)
  {
      node = node->next; //iterate to p;
  }
  node = node->next; //Get to the node after p that is to be deleted
  node->prev->next = node->next;
  node->next->prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}

// remove the node before the node p
template <typename T>
T DLList<T>::remove_before(DLListNode<T> &p)
{
  if(this->is_empty())
  {
    throw EmptyDLList("Empty Doubly Linked List");
  }
  if(&p == &header)
  {
    throw "Cant remove after header node";
  }
  if(&p == header.next)
  {
    throw "Cant remove header node";
  }
  DLListNode<T> *node = header.next;
  while(node != &p)
  {
      node = node->next;
  }
  node = node->prev;
  node->next->prev = node->prev;
  node->prev->next = node->next;
  T obj = node->obj;
  delete node;
  return obj;
}

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll)
{  
  DLListNode<T> *node = dll.first_node();

  while(node != dll.after_last_node())
  {
    out << node->obj;
    out << endl;
    node = node->next;
  }

  return out;
}
