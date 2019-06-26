/*
If:
Company A owns 10% of Company B,
Company B owns 5% of Company C,
Company B owns 5% of Company D,
Company A owns 2% of Company C

then, how much of Company C does A own? 2.5%
*/
#include <iostream>
#include <tuple>
#include <vector>
#include <unordered_map>

using namespace std;

float dfs(unordered_map<char, unordered_map<char,float>>& adjList, char p, char p1, char c, unordered_map<char,int>& visited) {
    if(visited[p] != 0) return 0;
    visited[p] = 1;
    float ret = 0.0;
    for(auto const& node : adjList[p]) {
        if(node.first == c) {
            
            if(p1 == p) {
                ret= node.second;
                
            }
            else {
                ret= node.second * adjList[p1][p];
            }
        }
        if(visited[node.first] == 0)
            ret+=dfs(adjList, node.first, p, c, visited);   
    }
    
    return ret;
}
float companyShares(vector<tuple<char,char,float>>& input, char parent, char child ) {
    unordered_map<char, unordered_map<char,float>> adjList;
    for(auto const& v : input) {
        adjList[std::get<0>(v)].insert({std::get<1>(v), std::get<2>(v)/100});
    }
    unordered_map<char,int> visited;
    return dfs(adjList, parent, parent, child, visited);
}

int main() {
    vector<tuple<char,char,float>> input = { std::make_tuple('A', 'B', 10.0),
                                            std::make_tuple('B', 'C', 5.0),
                                            std::make_tuple('B', 'D', 5.0),
                                            std::make_tuple('A', 'C', 2.0),
                                        };
    cout << companyShares(input, 'A', 'B') * 100 <<endl;

    return 0;
}