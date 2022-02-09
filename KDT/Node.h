#include <iostream>
#include <vector>

using namespace std;

const int k=2;

class Points
{
public:
    vector<int> points;
    bool operator==(Points &tmp);
};

class Node : public Points
{
    Node* left;
    Node* right;

public:
    Node(vector<int>points);
    void setLeft(Node* child);
    void setRight(Node* child);
    Node* getLeft();
    Node* getRight();
};