#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <stack>

using namespace std;
unordered_map<string,vector<string>> nodeMap;
unordered_map<string,bool> valMap;

void parseString(string& ip) {
    stringstream ss(ip);
    string rel;
    while(getline(ss, rel, ';')){
        auto it = rel.find_first_of('-');
        string parent = rel.substr(0,it);
        string child = rel.substr(it+2);
        nodeMap[child].push_back(parent);
        if(!nodeMap.count(parent))
            nodeMap[parent] = vector<string>();
    }
}

void computeVal() {
    stack<string> stk;
    for(auto const& node : nodeMap) {
        if(node.second.empty())
            valMap[node.first] = false;
        else {
            stk.push(node.first);
            for(auto const& val : node.second) {
                if(valMap.count(val)) {
                    if(valMap[val] == false){
                        valMap[node.first] = false;
                        stk.pop();
                        break;
                    } else {
                        stk.push(node.first);
                    }

                }
            }
        }
    }
}


int main() {
    string  ip = "a->b;b->c;c->d";
    parseString(ip);
    computeVal();
    for(auto const& val : valMap)
        cout << val.first <<" : "<< val.second<<endl;
    cout << endl;
    

}