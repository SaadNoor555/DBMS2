#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

#ifndef MAX
#define D 2
#define MAX 6
#endif
#define Debug(x) cout<< #x<< ": "<< x<< "\n";

using namespace std;

class Node {
    bool IS_LEAF;
    // wstring* key;
    string* key;
    string* meaning;
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
    void insertInternal(string, string, Node *, Node *);
    Node *findParent(Node *, Node *);

public:
    BPTree();
    Node* search(string, int& pos);
    bool insert(string, string);
    void display(Node *);
    Node *getRoot();
    void query();
};