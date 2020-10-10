#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "strutils.h"

using namespace std;

template <class itemType>
class LinkedList;

template <class itemType>
struct node {
    itemType info; // has info inside
    node<itemType> *next; // points next node
    LinkedList<int> * numList; // points a integer linkedlist
    
    node () // default constructor
    {}
    
    node (const itemType & s, node * link) // constructor with info and next pointer
    : info(s), next (link)
    { }
    
};

template <class itemType>
class LinkedList
{
private:
    node<itemType> * head; // head of linked list
public:
   
    node<itemType> * getHead(); // used for print function
    void insert(LinkedList<int> * listNum, int docNum); // insertion of new node (int type)
    LinkedList (); // default constructor
    ~LinkedList ();   //destructor
    void printList(); // prints list
    void AddInOrder(itemType newkey, int docNum); // inserts in sorted order with string and integer
    void AddInOrder(itemType docNum); // insters in sorted order with integer only
    vector<int> infos(); // fills the vectors to compare
    node<itemType> * returnNode(itemType name); //finds the node and returns it , else returns NULL
};


/*---------------------------------------------------------------
 @@@@@@@@@@@@@@@@@@@@@ F U N C T I O N S @@@@@@@@@@@@@@@@@@@@@@@
 ---------------------------------------------------------------*/
template <class itemType>
node<itemType> * LinkedList<itemType>::getHead(){
    return head;
}

template <class itemType>
void LinkedList<itemType>::insert(LinkedList<int> * listNum, int docNum){

    listNum->head = new node<int>(docNum,NULL);
    
}

template <class itemType>
void LinkedList<itemType>::AddInOrder(itemType newkey, int docNum)
{
    LinkedList<int> * listNum = new LinkedList<int>;
    listNum->insert(listNum, docNum);
    
    node<itemType> * ptr = head;
    if (head == NULL || UpperString(newkey) < UpperString(head->info)){
            head =  new node<itemType>(newkey, head);
            head->numList = listNum;
            return;
    }

    while (ptr->next != NULL && UpperString(ptr->next->info) < UpperString(newkey)){
        ptr = ptr->next;
    }
    ptr->next = new node<itemType>(newkey,ptr->next);
    ptr->next->numList = listNum;
}
    
    
template <class itemType>
void LinkedList<itemType>::AddInOrder(itemType docNum)
{ // if we will add only number
    node<int> * ptr = head;
        
    if (head == NULL || docNum < head->info)
    {
        head =  new node<int>(docNum, head);
        return;
    }
    while (ptr->next != NULL && ptr->next->info <= docNum)
    {
        ptr = ptr->next;
    }
    if(ptr->info == docNum)
        return;
        
    ptr->next = new node<int>(docNum,ptr->next);
}

template <class itemType>
vector<int> LinkedList<itemType>::infos()
{
    vector<int> *returnVector = new vector<int>;
    node<int> * temp = head;
    while(temp != NULL && temp->next != NULL){
        returnVector->push_back(temp->info);
        temp = temp->next;
    }
    returnVector->push_back(temp->info);
    return *returnVector;
}

template <class itemType>
LinkedList<itemType>::~LinkedList ()
{
    node<itemType> * ptr = head;
    while (ptr != NULL)
    {
        node<itemType> * temp = ptr->next;
        delete ptr;
        ptr = temp;
    }
}

template <class itemType>
LinkedList<itemType>::LinkedList ()
{
    head = NULL;
}

template <class itemType>
node<itemType> * LinkedList<itemType>::returnNode(itemType name)
{
    node<itemType> *temp = head;
    
    while( temp != NULL && temp->next != NULL )
    {
        if(temp->info==name)
            return temp;
        else
            temp=temp->next;
    }
    if(temp != NULL && temp->info==name)
        return temp;
    else
        return NULL;
}

template <class itemType>
void LinkedList<itemType>::printList ()
{
    node<itemType> * ptr = head;
    int i = 0;
    while (ptr != NULL)
    {
        string a = ptr->info;
        cout << endl;
        cout << i << ": "<< ptr->info  <<endl;
        for(int i = 0; i< (a.length() + 3); i ++)
            cout << "-" << endl;
        LinkedList<int> * elma = ptr->numList;
        node<int> * headCopy;
        headCopy = elma->getHead();
        node<int> * armut = headCopy;
        while(armut != NULL){
            cout << armut->info << " ";
            armut = armut->next;
        }
        ptr = ptr->next;
        i++;
        cout << endl ;
    }
    cout << endl;
}


#endif

