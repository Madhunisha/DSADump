#include <iostream>
#include<stdio.h> 
#define my_sizeof(type) (char*)(&type+1)-(char* )(&type)

using namespace std;

int main() {
    uint v = 678;
    cout << my_sizeof(v);
    return 0;
}

