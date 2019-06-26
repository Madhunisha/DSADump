#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

vector<string> primAl(vector<tuple<char,char,int>>& ip) {
    unordered_map<char,vector<pair<char,int>>> adjList;
    for(auto const& val : ip) {
        adjList[get<0>(val)].emplace_back(get<1>(val),get<2>(val));
        adjList[get<1>(val)].emplace_back(get<0>(val),get<2>(val));
    }
    int n = adjList.size();
    unordered_map<char,int> dist;
    for(auto const& val : adjList) {
        dist[val.first] = INT_MAX;
    }
    unordered_map<char,char> path;
    unordered_map<char, char> map;
    unordered_set<char> inMst;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    char src = (*adjList.begin()).first;
    vector<string> result;
    pq.push({0,src});
    while(!pq.empty()) {
        auto u = pq.top();
        pq.pop();
        inMst.insert(u.second);
        for(auto const& val : adjList[u.second]) {
            char v = val.first;
            int wt = val.second;
            if(!inMst.count(v) && dist[v] > wt) {
                dist[v] = wt;
                pq.push({wt,v});
                path[v] = u.second;
            }

        }


    }
    for(auto const& val : path)
    result.push_back(string(1,val.first)+string(1,val.second));
    return result;
}

int main() {
    vector<tuple<char,char,int>> ip = {std::make_tuple('A', 'D', 1),
                                        std::make_tuple('A', 'B', 3),
                                        std::make_tuple('B', 'D', 3),
                                        std::make_tuple('B', 'C', 1),
                                        std::make_tuple('D', 'C', 1),
                                        std::make_tuple('D', 'E', 6),
                                        std::make_tuple('C', 'E', 5),
                                        std::make_tuple('C', 'F', 4),
                                        std::make_tuple('E', 'F', 2),
                                    };
    vector<string> ret = primAl(ip);
    for(auto& val : ret)
        cout << val <<endl;
    return 0;
}