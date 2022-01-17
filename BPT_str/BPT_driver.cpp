// Searching on a B+ tree in C++

#include "bpt_header.h"
#include <fstream>
#include <windows.h>

int main() 
{
    int cnt=0;
    BPTree node;
    ifstream in;
    wstring line, eng;
    wstring ban;
    in.open("dic.txt", ios::in);
    while(getline(in, line))
    {
        int pos= line.find("|", 1);
        eng= line.substr(1, pos-1);
        ban= line.substr(pos+1);
        node.insert(eng);
    }
    // node.display(node.getRoot());
    // string s;
    // do
    // {
    //     cin>> s;
    //     if(node.search(s))
    //         cout<< "Found\n";
    //     else
    //         cout<< "Not Found\n";
    // }while(s!="end");
    cout<< int(ban[0])<< endl;

    in.close();
    

}