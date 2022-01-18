// Searching on a B+ tree in C++

#include "bpt_header.h"
#include <fstream>
#include <windows.h>

int main() 
{
    int cnt=0;
    BPTree node;
    bool flag=1;
    ifstream in;
    string line, eng, ban;
    in.open("dic.txt", ios::in);
    while(getline(in, line))
    {
        int pos= line.find("|", 1);
        eng= line.substr(1, pos-1);
        ban= line.substr(pos+1);
        flag &= node.insert(eng, ban);
    }
    if(flag)
        cout<< "B+ Tree Created Successfully\nInsert strings to find: \n";
    else
        cout<< "B+ Tree Creation Failed\n";
    // cout
    // node.display(node.getRoot());
    string s;
    do
    {
        cin>> s;
        cout<< node.search(s)<< endl;
    }while(s!="end");

    in.close();
    

}