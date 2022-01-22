// implementation of the DLList class

#include <stdexcept>
#include "DLList.h"


// extend runtime_error from <stdexcept>
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};

// copy constructor
DLList::DLList(const DLList& dll)
{
  header.next = &trailer;
  trailer.prev = &header;
  DLListNode *temp = dll.header.next;
  while(temp != dll.after_last_node())
  {
    this->insert_last(temp->obj);
    temp = temp->next;
  }
}

// move constructor
DLList::DLList(DLList&& dll)
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
DLList& DLList::operator=(const DLList& dll)
{
  if(this != &dll)
  {
    DLListNode *temp = this->header.next;
    while(temp != &trailer)
    {
      delete temp;
      temp = temp->next;
    }
  }

  header.next = &trailer;
  trailer.prev = &header;
  DLListNode *node = dll.header.next;
  while(node != dll.after_last_node())
  {
    this->insert_last(node->obj);
    node = node->next;
  }
}

// move assignment operator
DLList& DLList::operator=(DLList&& dll)
{
  if(dll.is_empty())
  {
    header.next = &trailer;
    trailer.prev = &header;
  }

  if(this != &dll)
  {
    DLListNode *temp = this->header.next;
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
DLList::~DLList()
{
  DLListNode *prev_node;
  DLListNode *node = header.next;

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
void DLList::insert_first(int obj)
{ 
  DLListNode *newNode = new DLListNode(obj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}

// insert a new object as the last one
void DLList::insert_last(int obj)
{
  DLListNode *newNode = new DLListNode(obj, trailer.prev, &trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

// remove the first node from the list
int DLList::remove_first()
{ 
  if(this->is_empty())
  {
    throw EmptyDLList("Empty Doubly Linked List");
  }
  DLListNode *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  int obj = node->obj;
  delete node;
  return obj;
}

// remove the last node from the list
int DLList::remove_last()
{
  if(this->is_empty())
  {
    throw EmptyDLList("Empty Doubly Linked List");
  }
  DLListNode *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  int obj = node->obj;
  delete node;
  return obj;
}

// return the first object (do not remove)
int DLList::first() const
{ 
  if(this->is_empty())
  {
    throw EmptyDLList("Empty Doubly Linked List");
  }
  return header.next->obj;
}

// return the last object (do not remove)
int DLList::last() const
{
  if(this->is_empty())
  {
    throw EmptyDLList("Empty Doubly Linked List");
  }
  return trailer.prev->obj;
}

// insert a new node after the node p
void DLList::insert_after(DLListNode &p, int obj)
{
  if(&p == &trailer)
  {
    throw "Cant insert after trailer node";
  }

  DLListNode *node = new DLListNode(obj, &p, p.next);
  node->prev->next = node;
  node->next->prev = node;
}

// insert a new node before the node p
void DLList::insert_before(DLListNode &p, int obj)
{
  if(&p == &header)
  {
    throw "Cant insert before header node";
  }

  DLListNode *node = new DLListNode(obj, p.prev, &p);
  node->prev->next = node;
  node->next->prev = node;
}

// remove the node after the node p
int DLList::remove_after(DLListNode &p)
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
  DLListNode *node = header.next;
  while(node != &p)
  {
      node = node->next; //iterate to p;
  }
  node = node->next; //Get to the node after p that is to be deleted
  node->prev->next = node->next;
  node->next->prev = node->prev;
  int obj = node->obj;
  delete node;
  return obj;
}

// remove the node before the node p
int DLList::remove_before(DLListNode &p)
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
  DLListNode *node = header.next;
  while(node != &p)
  {
      node = node->next;
  }
  node = node->prev;
  node->next->prev = node->prev;
  node->prev->next = node->next;
  int obj = node->obj;
  delete node;
  return obj;
}

// output operator
ostream& operator<<(ostream& out, const DLList& dll)
{  
  DLListNode *node = dll.first_node();

  while(node != dll.after_last_node())
  {
    out << node->obj;
    out << endl;
    node = node->next;
  }

  return out;
}
