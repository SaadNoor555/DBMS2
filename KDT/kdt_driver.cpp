#include "Node.h"

#ifndef NODE_H
#define NODE_H

int main()
{
    Node* root=NULL;

    int numOfPoints;
    vector<int>inPoints(k);
    cout<< "Insert number of points: ";
    cin>> numOfPoints;
    cout<< "Insert the points:\n";
    for(int i=0; i<numOfPoints; i++)
    {
        for(int j=0; j<k; j++)
            cin>> inPoints[j];
        
        root= insertNode(root, inPoints, 0);
    }
    cout<< "KD Tree created\nThe tree in postorder:\n";
    printKDT(root);
    // return 0;
    while(1)
    {
        vector<int>p1(k);
        vector<int>p2(k);
        cout<< "Insert the search range (p1, p2):\n";
        for(int i=0; i<k; i++)
            cin>> p1[i];

        if(p1[0]<0) break;

        for(int i=0; i<k; i++)
            cin>> p2[i];
        vector<Point>result;

        searchRange(root, Point(p1), Point(p2), 0, result);
        printSearchRes(result);
        result.clear();
    }
}

#endif

/*
Test Input:
7
3 6
2 7
17 15
6 12
13 15
9 1
10 19
*/