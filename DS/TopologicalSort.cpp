#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;
unordered_map<string,vector<string>> nodeMap;

void parseString(string& ip) {
    stringstream ss(ip);
    string rel;
    while(getline(ss, rel, ';')){
        auto it = rel.find_first_of('-');
        string parent = rel.substr(0,it);
        string child = rel.substr(it+2);
        nodeMap[parent].push_back(child);
        if(!nodeMap.count(child))
            nodeMap[child] = vector<string>();
    }
}
void dfs(string source, vector<string>& result, unordered_map<string,bool>& visited) {
    visited[source] = true;
    for(auto const& node : nodeMap[source] ){
        if(visited[node] == false) {
            dfs(node, result, visited);
        }
    }
    result.push_back(source);
}

vector<string> topSort() {
    unordered_map<string,bool> visited(nodeMap.size());
    for(auto const& node : nodeMap)
        visited[node.first] = false;
    vector<string> result;

    for(auto const& node : nodeMap) {
        if(visited[node.first] == false) {
            dfs(node.first, result, visited);
        }
    }
    reverse(result.begin(),result.end());
    return result;
}
int main() {
    string  ip = "a->b;a->c;d->c;c->b";
    parseString(ip);
    auto ret = topSort();
    for(auto const& val : ret)
        cout << val <<", ";
    cout << endl;
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
}