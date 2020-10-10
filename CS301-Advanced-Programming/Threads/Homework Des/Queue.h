//Modified by Gizem Gezici
//Modified Date: 21.03.2012

#ifndef DYNINTQUEUE_H
#define DYNINTQUEUE_H
#include <string>
using namespace std;

struct QueueNode
{
	string value;
	QueueNode *next;
	QueueNode(string val, QueueNode *ptr = NULL)
	{
		value = val;
		next = ptr;
	}
};

class Queue
{
	private:
		// These track the front and rear of the queue.
		QueueNode *front;
		QueueNode *rear;	
	public:
		// Constructor.
		Queue();
	
		// Member functions.
		void enqueue(string);
		void dequeue(string &);
		bool isEmpty() const;     
		void clear();
};
#endif