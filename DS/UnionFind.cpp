#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
class UnionF {
    private:
    class Node {
    public:
        int data;
        int rank;
        Node* parent;
    };
    unordered_map<int,Node*> pool;
public:
UnionF(){
}
UnionF(vector<vector<int>>& grid){
    int m=grid.size(), n=grid.size();
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            makeSet(grid[i][j]);
        }
    }
}

void makeSet(int val){
    Node* node = new Node();
    node->data = val;
    node->rank = 0;
    node->parent = node;
    pool[val] = node;

}
 
 //Path Compression
Node* findSet(Node* n){
    if(n->parent == n) return n;
    n->parent = findSet(n->parent);
}

int findSet(int n){
    return findSet(pool[n])->data;
}

bool unionNode(int v1, int v2){
    Node* n1 = pool[v1];
    Node* n2 = pool[v2];

    Node* p1 = findSet(n1);
    Node* p2 = findSet(n2);
    if(p1->data == p2->data) return false;

    if(p1->rank >= p2->rank){
        p1->rank = (p1->rank == p2->rank)?p1->rank+1:p1->rank;
        p2->parent = p1;
    } else {
        n1->parent = n2;
    }
    return true;
}

};

int main() {
    vector<vector<int>> grid = {{1,1,1,1,0},
                                {1,1,0,1,0},                
                                {1,1,0,0,0},
                                {0,0,0,0,0},
                                };
    UnionF uf(grid);
    
}