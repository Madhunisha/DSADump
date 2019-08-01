#include <iostream>
#include <unordered_map>
#include <queue>
#include <climits>

using namespace std;

/**
#include <vector>
std::vector<std::vector<int>> wizards = {
  {1, 2, 3},   // wizard 0
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

0->1->4->6->9
    
cost(i,j) = (i-j)^2 if i knows j
cost(0->1->4->6->9) = (0-1)^2 + (1-4)^2 + (4-6)^2 + (6-9)^2 = 1 + 9 + 4 + 9 = 23

Question: Given a start and an end wizards, find the path of the minimum cost going from start to end.
*/

//vector<int> findRelation(std::vector<std::vector<int>>& wizards, int st, int end) {
int findRelation(std::vector<std::vector<int>>& wizards, int st, int end) {
  unordered_map<int, vector<pair<int,int>>> adjList;
  for(int i=0;i<(int)wizards.size();i++) {
    for(auto const& wiz : wizards[i]) {
      int wt = (wiz-i) * (wiz-i); // 0 -> 1,2,3 . 
      adjList[i].emplace_back(wiz,wt);
    }
  }
  // 0-> [[1,1],[2,4],[3,9]]
  vector<bool> visited(wizards.size());
  vector<int> result;
  // intermediate path to be updated into the result
  vector<int> intResult;
  int minCost = INT_MAX;
  queue<pair<int,int>> q;
  q.push({st,0});
  visited[st] = true;
  
  while(!q.empty()) {
  
      auto front = q.front();
      auto costF = front.second;
      q.pop();
      
      if(front.first == end){ 
        if(costF < minCost){
          result = intResult;
          minCost = costF;
        } else {
          intResult.clear();
        }
      }

      for(auto const& knownWiz : adjList[front.first]) {
        if(visited[knownWiz.first] || (knownWiz.second + costF > minCost)) {
           continue;
        }
        visited[knownWiz.first] = true;
        q.push({knownWiz.first, costF + knownWiz.second}); 
        cout << knownWiz.first << "|"<< knownWiz.second <<"|" << costF <<endl;
      }
     //cost=costF; // 0->1->8  cost = 50 
  
  }
  return minCost==INT_MAX?-1:minCost;
  
}
// To execute C++, please define "int main()"
int main() {
  std::vector<std::vector<int>> wizards = {
  {1},   // wizard 0
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
  
cout << findRelation(wizards, 0,9) << endl;
  return 0;
}
