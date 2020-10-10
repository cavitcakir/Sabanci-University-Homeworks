/*************************************
*Modified by Gizem Gezici
*Date: 05.03.2012
*************************************/

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <string>
using namespace std;

struct node
 {
     string name;
     int price;
     int quantity;
     node *next;
     node *prev;
     
     node()
     :quantity(0), price(0)
     {}

     node(const string &s, node * link, node * back, int a, int d)
		: name(s), next(link), prev(back), quantity(a), price(d)
     {}
};

class linkedlist
{
private:
    node *head;		//Head node, start of LinkedList
    void printListInverse(node *n);
    void deleteAll(node*head);

public:
    linkedlist();			//Constructor
	void printList();		//Prints the given LinkedList from head to end
	void printListInverse();//Prints the given LinkedList from end to head
    void AddInOrder(string name, int quantity, int price, int selected);
    int deleteOneNode (string name);
    bool checkExist(string name);
    void totalCost();
    node * returnNode(string name);
    void deleteAll();
};


#endif
