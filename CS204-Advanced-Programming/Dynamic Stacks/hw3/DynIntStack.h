#ifndef _DYNINTSTACK_H
#define _DYNINTSTACK_H

#include <string>
using namespace std;

struct StackNode
{
	string word;
	StackNode *next;
};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack(void);
	void push(string);
	void pop(string &);
	bool isEmpty(void);
};

#endif
