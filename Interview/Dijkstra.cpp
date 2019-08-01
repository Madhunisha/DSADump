#include <iostream>
#include <unordered_map>
#include <queue>
#include <climits>
#include <set>

using namespace std;

int findRelation(std::vector<std::vector<int>>& wizards, int st, int end) {
    unordered_map<int, vector<pair<int,int>>> adjList;
    for(int i=0;i<(int)wizards.size();i++) {
        for(auto const& wiz : wizards[i]) {
            int wt = (wiz-i) * (wiz-i); // 0 -> 1,2,3 . 
            adjList[i].emplace_back(wiz,wt);
        }
    }
    int minCost = INT_MAX;
    set<pair<int,int>> s;
    unordered_map<int,int> dist;
    unordered_map<int,int> parent;
    for(auto& val : adjList ) {
        dist[val.first] = INT_MAX;
    }  
    s.insert(make_pair(0,st));
    dist[st] = 0;
    parent.emplace(st,st);
    while(!s.empty()) {
        auto front = *(s.begin());
        int node = front.second;
        int nodeDist = front.first;
        s.erase(s.begin());
        if(node == end) {
            if(nodeDist < minCost)
                minCost = nodeDist;
        }
        for(auto const& childPair : adjList[node]) {
            if(nodeDist + childPair.second < dist[childPair.first]) {
                auto f = s.find(make_pair(dist[childPair.first],childPair.first));
                if(f != s.end()) 
                    s.erase(f);
                s.insert(make_pair(nodeDist + childPair.second, childPair.first));
                dist[childPair.first] = nodeDist + childPair.second;
                parent[childPair.first] = node;
            }
        }
    }
    vector<int> ret;
    ret.push_back(end);
    do { 
        ret.push_back(parent[end]);
        end = parent[end];

    }while(parent[end] != end );
    reverse(ret.begin(),ret.end());
    for(auto const& val :ret) {
        cout <<val <<",";
    }
    cout <<endl;
    return minCost;
}

int main() {
  std::vector<std::vector<int>> wizards = {
  {1,2,3},   // wizard 0
  {8, 6, 4},   // wizard 1
  {7, 8, 3},   // wizard 2
  {8, 1},      // wizard 3 knows 8, 1
  {6},         // wizard 4 knows 6
  {8, 7},      // wizard 5 knows 8, 7
  {9, 4},      // wizard 6 knows 9, 4
  {4, 6},      // wizard 7 knows 4, 6
  {1},         // wizard 8 knows 1
  {1, 4},      // wizard 9 knows 1, 4
};
  
cout << findRelation(wizards, 0,8) << endl;
  return 0;
}
