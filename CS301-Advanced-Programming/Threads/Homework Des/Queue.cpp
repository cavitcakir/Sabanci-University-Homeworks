//Modified by Gizem Gezici
//Modified Date: 21.03.2012
#include <iostream>
#include "Queue.h"
using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
Queue::Queue()
{
	front = NULL;
	rear = NULL;
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void Queue::enqueue(string val)
{       
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(val);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(val);
		rear = rear->next;
	} 
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void Queue::dequeue(string &val)
{
	QueueNode *temp;
	if (isEmpty())
	{
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		val = front->value;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool Queue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void Queue::clear()
{
	string val;   // Dummy variable for dequeue

	while(!isEmpty())
		dequeue(val); //delete all elements
}
