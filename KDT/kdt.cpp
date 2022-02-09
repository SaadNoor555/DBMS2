#include "Node.h"

#ifndef NODE_H
#define NODE_H


Node* insertNode(Node *curNode, vector<int> points, int lvl)
{
    if(curNode==NULL)
    {
        Node *newNode= new Node(points);
        return newNode;
    }
    int c_axis = lvl % k;

    if(points[c_axis] < curNode->points[c_axis])
        curNode->setLeft(insertNode(curNode->getLeft(), points, ++lvl));
    else
        curNode->setRight(insertNode(curNode->getRight(), points, ++lvl));

    return curNode;
}

void searchRange(Node* curNode, Point p1, Point p2, int lvl, vector<Point>& res)
{
    if(curNode==NULL)
        return;

    int c_axis = lvl%k;
    int mn = min(p1.points[c_axis], p2.points[c_axis]);
    int mx = max(p1.points[c_axis], p2.points[c_axis]);

    if(curNode->points[c_axis]>=mn && curNode->points[c_axis]<=mx)
    {
        searchRange(curNode->getLeft(), p1, p2, lvl+1, res);
        searchRange(curNode->getRight(), p1, p2, lvl+1, res);
    }
    else if(curNode->points[c_axis]<mn)
        searchRange(curNode->getRight(), p1, p2, lvl+1, res);
    
    else
        searchRange(curNode->getLeft(), p1, p2, lvl+1, res);

    if(curNode->isBetween(p1, p2))
        res.push_back(Point(curNode->points));
}

void printKDT(Node* curNode)
{
    if(curNode==NULL)
        return;

    printKDT(curNode->getLeft());
    printKDT(curNode->getRight());

    cout<< '(';
    for(int j=0; j<k; j++)
    {
        cout<< curNode->points[j];
        if(j<k-1) cout<< ',';
        else cout<< ')';
    }
    cout<< endl;
}

void printSearchRes(vector<Point>result)
{
    cout<< "Number of points in range: "<< result.size()<< endl;
    for(int i=0; i<result.size(); i++)
    {
        cout<< '(';
        for(int j=0; j<k; j++)
        {
            cout<< result[i].points[j];
            if(j<k-1) cout<< ',';
            else cout<< ')';
        }
        cout<< endl;
    }
}

Point :: Point(vector<int>points)
{
    this->points= points;
}

Point :: Point()
{

}

bool Point :: operator==(Point &tmp)
{
    for(int i=0; i<k; i++)
        if(tmp.points[i]!=this->points[i])
            return 0;

    return 1;
}

Node :: Node()
{

}

Node :: Node(vector<int>points)
{
    this->points = points;
    this->setLeft(NULL);
    this->setRight(NULL);
}

void Node :: setLeft(Node* child)
{
    this->left= child;
}

void Node :: setRight(Node* child)
{
    this->right= child;
}

Node* Node :: getLeft()
{
    return this->left;
}

Node* Node :: getRight()
{
    return this->right;
}

bool Node :: isBetween(Point p1, Point p2)
{
    for(int i=0; i<k; i++)
    {
        int mx= max(p1.points[i], p2.points[i]);
        int mn= min(p1.points[i], p2.points[i]);
        if(this->points[i]<mn || this->points[i]>mx)
            return false;
    }
    return true;
}

#endif