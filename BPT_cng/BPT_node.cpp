#include "bpt_header.h"

#ifndef MAX
#define MAX 3
#endif

Node::Node() 
{
	key = new int[MAX];
	ptr = new Node *[MAX + 1];
}

Node::~Node()
{
	delete[] key;
	for(int i=0; i<=MAX; i++)
		delete[] ptr[i];
}
