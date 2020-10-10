#include <iostream>
#include "linkedList.h"

using namespace std;

linkedlist::linkedlist()
{
	head=NULL;
}

void linkedlist::printList()
{
    if (head == NULL) // if the list is empty
    {
        cout<< "Houston, we have a problem!! list is empty!\n";
   	}
    else
    {
        cout << "[" << head->id << "][" << head->size << "][" << head->index << "]";

        node * n = head->next;
        while(n != NULL)// print until the end of list
        {
          cout << "---[" << n->id << "][" << n->size << "][" << n->index << "]";
          n = n->next;
        }
      	cout << "\n";
    }
}

int linkedlist::checkList(const int & size)
{
    node *temp = head;
    int flag = -1;

    while(temp != NULL && flag == -1)
    {
        if(temp->size >= size && temp->id == -1) //find good place for our request
            flag = temp->index; //return that points index
        else
            temp=temp->next;
    }
    return flag;
}
void linkedlist::freeTheMemory (const int & id, const int & size, const int & MEMORY_SIZE)
{
    node * temp = head;
    bool flag = true;

    if(head==NULL)// if list is empty -> it shouldn't be any time
    {
        cout<< "\n!!!ERROR!!!\nHouston, we have a problem, freeMemory1\n!!!ERROR!!!\n\n";
    }
    else
    {
        while(temp != NULL && flag)
        {
            if(temp->id == id && temp->size == size) // find the place of our request
                flag = false;
            else
                temp=temp->next;
        }
        if(!flag){ // if a place found
          node *toBeDeleted = temp;
          node * ptr;
          if(toBeDeleted == head){ // if we are going to free the first element
            head->id = -1;
            if(toBeDeleted->next->id == -1){ // if next of first element is hole
              toBeDeleted->size += toBeDeleted->next->size;
              if(toBeDeleted->next->next != NULL)
                toBeDeleted->next->next->prev = toBeDeleted;
              toBeDeleted->next = toBeDeleted->next->next;
            }
          }
          else if(toBeDeleted->next == NULL){ // if we are going to free the last element
            if(toBeDeleted->prev->id == -1){ // if previous of last element is hole
              toBeDeleted->prev->size += toBeDeleted->size;
							toBeDeleted->prev->next = NULL;
              delete toBeDeleted;
            }
            else{
              toBeDeleted->id = -1;
            }
          }
          else{ // if we are going to free the middle element
            if(toBeDeleted->prev->id == -1 && toBeDeleted->next->id == -1){ // if left and right is hole
              toBeDeleted->prev->size += toBeDeleted->size;
              toBeDeleted->prev->size += toBeDeleted->next->size;
              if(toBeDeleted->next->next != NULL)
                toBeDeleted->next->next->prev = toBeDeleted->prev;
              toBeDeleted->prev->next = toBeDeleted->next->next;
              delete toBeDeleted->next;
              delete toBeDeleted;
            }
            else if(toBeDeleted->next->id == -1){// if only right of it is hole
              ptr = toBeDeleted->next;
              toBeDeleted->size += toBeDeleted->next->size;
              if(toBeDeleted->next->next != NULL)
                toBeDeleted->next->next->prev = toBeDeleted;
              toBeDeleted->next = toBeDeleted->next->next;
							toBeDeleted->id = -1;
              delete ptr;
            }
            else if(toBeDeleted->prev->id == -1 ){ // if only left of it is hole
              toBeDeleted->prev->size += toBeDeleted->size;
              toBeDeleted->next->prev = toBeDeleted->prev;
              toBeDeleted->prev->next = toBeDeleted->next;
              delete toBeDeleted;
            }
						else{ // if left and right is not hole
							toBeDeleted->id = -1;
						}
          }
        }
        else{ // if we are trying to delete something that is not in linkedlist
          cout<< "\n!!!ERROR!!!\nHouston, we have a problem freeMemory2 id: " << id <<" size:" <<size<< "\n!!!ERROR!!!\n\n";
        }
    }
}


void linkedlist::allocateMemory(const int & id, const int & size)
{
  node * ptr = head;
  if (head == NULL) // if list is empty
  {
      head = new node(NULL, NULL, id, size, 0);
  }
  else{
    while(ptr != NULL && !(ptr->id == -1 && ptr->size >= size)){ // find suitable place for our request
      ptr = ptr->next;
    }
    if (ptr != NULL && ptr->id == -1 && ptr->size >= size) { // we found
      int residual = ptr->size - size; // calculate residual
      if(residual == 0){ // if size is exactly what we are asked for
        ptr->id = id;
      }
      else{ // we have residual after we allocate memory for our request
        ptr->id = id;
        ptr->size = size;
        node * residualHole = new node(ptr->next, ptr, -1, residual, ptr->index + ptr->size);// create hole
        ptr->next = residualHole;
        if(residualHole->next != NULL)
          residualHole->next->prev = residualHole;
      }
    }
  }
}

void linkedlist::deleteAll()
{// free the memory
  while(head != NULL)
  {
      node * temp = head;
      head = head->next;
      delete temp;
  }
}
