#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <string>
using namespace std;

struct node
 {
     int id;
     int size;
     int index;
     node *next;
     node *prev;

     node(node * nxt, node * back, const int & s, int a, int d)
     :id(s), next(nxt), prev(back), size(a), index(d)
     {}
};

class linkedlist
{
private:
    node *head;		//Head node, start of LinkedList

public:
    linkedlist();			//Constructor
    int checkList(const int & size); // done
    void allocateMemory(const int & id, const int & size);//done
    void freeTheMemory(const int & id, const int & size, const int & MEMORY_SIZE);//done
  	void printList(); // done
    void deleteAll();
};


#endif
