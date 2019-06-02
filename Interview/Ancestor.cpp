#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>

using namespace std;
/* Given a vector of pairs {child,parent}. Return if the two children share the same ancestor
//  1   2   4
     \ /   / \
      3   5  10
       \ / \  \
        6   7  8

In the above graph 3,5 do not have a common ancestor. However, 6,8 share a common ancestor 4
*/
vector<int> bfs(unordered_map<int,vector<int>>& adjList, queue<int>& q){
    vector<int> result;
    //int lvl=0;
    while(!q.empty()) {
        int qsize = q.size();
        for(int i=0;i<qsize;i++){
            auto f = q.front();
            q.pop();
            result.push_back(f);
            for(auto const& v : adjList[f]){
                q.push(v);
            }
        }
    }
    return result;
}

int findParent(vector<pair<int,int>>& cpPair, int x, int y){
    unordered_map<int,vector<int>> adjList;
    for(auto const& v : cpPair){
        adjList[v.first].push_back(v.second);
        if(!adjList.count(v.second)){
            adjList[v.second]=vector<int>();
        }
    }
    queue<int> qx,qy;
    qx.push(x);
    qy.push(y);
    vector<int> ancx = bfs(adjList,qx);
    vector<int> ancy = bfs(adjList,qy);

    for(auto const& xv : ancx) {
        for(auto const& yv : ancy){
            if(xv == yv)
                return xv;
        }
    }
    return -1;
}

int main() {
    vector<pair<int,int>> childParentPairs = {
                                                {3,1},
                                                {3,2},
                                                {6,3},
                                                {6,5},
                                                {5,4},
                                                {7,5},
                                                {10,4},
                                                {8,10}
    };
    cout << findParent(childParentPairs,6,7);
    return 0;
}