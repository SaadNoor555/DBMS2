#include <iostream>
#include <vector>

using namespace std;

const int k=2;

class Point
{
public:
    vector<int>points;
    Point(vector<int>points);
    Point();
    bool operator==(Point &tmp);
};

class Node : public Point
{
    Node* left;
    Node* right;

public:
    Node();
    Node(vector<int>points);
    void setLeft(Node* child);
    void setRight(Node* child);
    Node* getLeft();
    Node* getRight();
    bool isBetween(Point p1, Point p2);
};

void printKDT(Node* curNode);
Node* insertNode(Node *curNode, vector<int> points, int lvl);
void searchRange(Node* curNode, Point p1, Point p2, int lvl, vector<Point>& res);
void printSearchRes(vector<Point>result);