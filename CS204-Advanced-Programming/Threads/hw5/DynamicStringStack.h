/*
Modified by Gizem Gezici
Date: 13.03.2012
Print member function was added
The name of the public clear function was modified
(in order to prevent function overloading)
*/


#ifndef DYNAMICSTRINGSTACK_H
#define DYNAMICSTRINGSTACK_H

#include <string>
using namespace std;

struct StackNode
{
	string value;
	StackNode *next;
};


class DynamicStringStack
{
	private:
		StackNode *top;
		StackNode* GetTopPointer(DynamicStringStack myStack);

	public:
		DynamicStringStack(void);
		void push(string);
		void pop(string &);
		bool isEmpty(void);
};


#endif