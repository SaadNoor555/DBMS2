#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

#ifndef MAX
#define MAX 3
#endif

using namespace std;

class Node {
    bool IS_LEAF;
    int *key, size;
    Node **ptr;
    friend class BPTree;

public:
    Node();
	~Node();
};

class BPTree 
{
    Node *root;
    void insertInternal(int, Node *, Node *);
    Node *findParent(Node *, Node *);

public:
    BPTree();
    void search(int);
    void insert(int);
    void display(Node *);
    Node *getRoot();
};