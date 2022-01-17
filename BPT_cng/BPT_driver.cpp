// Searching on a B+ tree in C++

#include "bpt_header.h"

int main() 
{
    BPTree node;
    int tlim=200;
    int errcnt= 0;
    for(int i=0; i<tlim; i+=5)
        node.insert(i);
    for(int i=1; i<tlim; i+=5)
        node.insert(i);
    for(int i=2; i<tlim; i+=5)
        node.insert(i);
    for(int i=4; i<tlim; i+=5)
        node.insert(i);
    for(int i=3; i<tlim; i+=5)
        node.insert(i);

    node.display(node.getRoot());

    for(int i=0; i<tlim; i++)
    {
        if(!node.search(i))
        {
            cout<< "error: "<< i<< endl;
            errcnt++;
            break;
        }
        
    }
    cout<< errcnt<<" errors out of "<< tlim<< endl;
}