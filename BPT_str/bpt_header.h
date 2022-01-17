#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

#ifndef MAX
#define D 2
#define MAX 7
#endif
#define Debug(x) cout<< #x<< ": "<< x<< "\n";

using namespace std;

class Node {
    bool IS_LEAF;
    // wstring* key;
    string* key;
    int size;
    Node **ptr;
    friend class BPTree;

public:
    Node();
	~Node();
};

class BPTree 
{
    Node *root;
    void insertInternal(string, Node *, Node *);
    Node *findParent(Node *, Node *);

public:
    BPTree();
    bool search(string);
    void insert(string);
    void display(Node *);
    Node *getRoot();
};