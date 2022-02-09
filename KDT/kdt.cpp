#include "Node.h"

#ifndef NODE_H
#define NODE_H


Node *insertNode(Node *curNode, vector<int> points, int axis)
{
    if(curNode==NULL)
        return &Node(points);

    int c_axis = axis % k;

    if(points[c_axis] < curNode->points[c_axis])
        curNode->setLeft (insertNode(curNode->getLeft(), points, ++axis));
    else
        curNode->setRight (insertNode(curNode->getRight(), points, ++axis));

    return curNode;
}



bool Points :: operator==(Points &tmp)
{
    for(int i=0; i<k; i++)
        if(tmp.points[i]!=this->points[i])
            return 0;

    return 1;
}

Node :: Node(vector<int>points)
{
    for(int i=0; i<k; i++)
        this->points[i]= points[i];

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

#endif