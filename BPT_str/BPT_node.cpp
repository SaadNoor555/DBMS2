#include "bpt_header.h"

#ifndef MAX
#define D 2
#define MAX 3
#endif

Node::Node() 
{
	key = new string[MAX + D];
	ptr = new Node*[MAX + 1 + D];
}

Node::~Node()
{
	delete[] key;
	for(int i=0; i<=MAX; i++)
		delete[] ptr[i];
}
