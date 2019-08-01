#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

using namespace std;

int addMul(string ip) {
    stringstream ss(ip);
    string temp;
    stack<string> opStk;
    stack<vector<int>> iStk;
    int val;
    while(getline(ss,temp, ' ')) {
        if(temp == ")") {
            if(opStk.empty())
                return val;
            else {
                if(iSt)
            }

        }
        else if(temp == "(") {

        }
    }
}