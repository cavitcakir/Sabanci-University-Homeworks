/*************************************
*Modified by Gizem Gezici
*Date: 05.03.2012
*************************************/

#include <iostream>
#include "linkedList.h"

using namespace std;

linkedlist::linkedlist()
{
	head=NULL;
}

void linkedlist::deleteAll()
{
    node * temp = head;
    if(head != NULL)
    {
        while(temp->next != head)
        {
            node * temp = head;
            head = temp->next;
            delete temp;
        }
        delete head;
    }
}

void linkedlist::deleteAll(node *temp)
{
        if (head != NULL)
        {
            deleteAll(head->next);
            delete head;
        }
}

void linkedlist::totalCost()
{
    node *temp;
    double cost =0;
    int count =0;
    if(head==NULL)
    {
        cout << "---\n"<< "The total estimated price of "<< count<<" kinds of items is: "<< cost << endl;
    }
    else
    {
        temp = head->next;
        cost = cost + ((head->quantity)*(head->price));
        count++;
        
        while(temp != head)
        {
            cost = cost + ((temp->quantity)*(temp->price));
            count++;
            temp=temp->next;
        }
    
        cout << "---\n"<< "The total estimated price of "<< count<<" kinds of items is: "<< cost << endl;
    }
}


node * linkedlist::returnNode(string name)
{
    node *temp = head;
    
    while(temp->next != head)
    {
        if(temp->name==name)
            return temp;
        else
            temp=temp->next;
    }
    return temp;
}

bool linkedlist::checkExist(string name)
{
    node *temp = head;
    bool flag = true;
    
    if(head==NULL)
    {
        flag =true;
    }
    else
    {
        if(temp->name==name)
            flag = false;
        else
            temp=temp->next;
        
        while(temp != head && flag)
        {
            if(temp->name==name)
                flag = false;
            else
                temp=temp->next;
        }
    }
    if(flag)
        return false;
    else
        return true;
}

int linkedlist::deleteOneNode (string name)
/* pre: toBeDeleted points to the node to be deleted from the list
 post: deletes the node pointed by toBeDeleted, updates head if changes */
{
    node *temp=head;;
    bool flag = true;
    
    if(head==NULL)
    {
        return 0;
        // cout<<"The shopping list is empty";
    }
    else
    {
        while(temp->next != head && flag)
        {
            if(temp->name==name)
                flag = false;
            else
                temp=temp->next;
        }
        if(temp->name==name)
            flag = false;
    
    node *toBeDeleted = temp;
    
    if(!flag)
    {
        node * ptr = head;
        node * last = head->prev;
        if (toBeDeleted == head)  //if the node to be deleted is the first node
        {
            if(head->next != head)
            {
            last->next = head->next;
            head->next->prev= last;
            head = head->next;
            delete toBeDeleted;
            }
            else
            {
               delete toBeDeleted;
                head = NULL;
            }
        }
        else  //if the node to be deleted is in the middle or at the end
        {
            while (ptr->next != toBeDeleted)
                ptr = ptr->next;
            //after while ptr point to the node just before toBeDeleted
        
            //connect the previous node to the next node and delete
            ptr->next = toBeDeleted->next;
            toBeDeleted->next->prev = ptr;
            delete toBeDeleted;
        }
        return 1;
        // cout << "The item "<<name<<" is deleted from the list."<< endl;
    }
    else
    {
        return 2;
        //  cout << "The item "<<name<<" could not be found in the list." << endl;
    }
    }
}


void linkedlist::printList()
{
    if (head == NULL)
    {
        cout<< "---\n" << "The shopping list is empty." << endl;
   }
    else
    {
        cout << "---" << endl << "Item: " << head->name << endl << "Quantity: " << head->quantity << endl << "Est. Price: " << head->price << endl;
        
        node * n = head->next;
        while(n != head)
        {
           cout << "---" << endl << "Item: " << n->name << endl << "Quantity: " << n->quantity << endl << "Est. Price: " << n->price << endl;
            n = n->next;
        }
    }
}


void linkedlist::printListInverse()
{
    
    if (head != NULL)
        printListInverse(head);
    else
    {
        cout << "---\n"<< "The shopping list is empty." << endl;
    }
}


void linkedlist::printListInverse(node *n)
{
	if(n->next != head)
	{
		printListInverse(n->next);
	}
    cout <<"---"<< endl <<"Item: " << n->name << endl << "Quantity: " << n->quantity << endl << "Est. Price: " << n->price << endl;
}


void linkedlist::AddInOrder(string name, int quantity, int price, int selected)
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list with newkey in it
{
    node *  ptr = head;   // loop variable
    node * ptr1 = head;
    // if new node should be first, handle this case and return
    // in this case, we return the address of new node since it is new head
    if (head == NULL )
    {
        head = new node(name, head, head, quantity, price);
        head->next = head;
        head->prev = head;
        
        if(selected == 1)
        cout << "---\nThe item " <<name<<" of quantity "<<quantity<<" is added to the list." << endl;
    }
    
    else if((quantity*price) > (head->price * head->quantity))
    {
        node * last = head;
      
        while(last->next != head)
            last = last->next;
            
        head = new node(name,ptr1,last,quantity,price);
        
        ptr1->prev = head;
        last->next = head;
        
        if(selected == 1)
            cout << "---\n"<< "The item " <<name<<" of quantity "<<quantity<<" is added to the list."<< endl;
    }
    
    else
    {
        node * prev = head; //to point to the previous node
        
        if(ptr->next == ptr)
        {
            ptr->next = new node(name,ptr,ptr,quantity,price);
            ptr->prev = ptr->next;
        }
        else
        {
            while(((ptr->price * ptr->quantity) >= (quantity*price)) && (prev->next != head))
            {
                ptr = ptr->next;
                prev = ptr->prev;
            }
            
        bool flag = true;
        if((prev->price * prev->quantity) == (quantity*price))
        {
             if((prev->name) > name)
                 flag = false;
        }
        
        
        if(flag)
        {
            prev->next = new node(name,ptr,prev,quantity,price);
            ptr->prev = prev->next;
        }
        else
        {
            node * doublePrev = prev->prev;
            doublePrev->next = new node(name,prev,doublePrev,quantity,price);
            prev->prev = doublePrev->next;
            
        }
        }
            
        if(selected == 1)
        cout << "---\n"<< "The item " <<name<<" of quantity "<<quantity<<" is added to the list."<< endl;
    }

}
