#include<iostream>
#include<io.h>
#include <fcntl.h>
#include<stdio.h>

// #define X 5

#ifndef X
#define X 2
#endif

using namespace std;

int main()
{
    // short x= 'শ';
    wchar_t* str= "ক";
    // SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_TEXT);
    wprintf(L"Interface %s\r\n", str);   //pszwName is a wchar_t*
}


