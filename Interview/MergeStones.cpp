#include <iostream>
#include <vector>

using namespace std;

int mergeStones(vector<int>& stones) {
    int n = stones.size();
    vector<vector<int>> dp(n+1,vector<int>(n+1));
    vector<int> sums(n+1);
    for(int i = 1; i<=n;i++)
        sums[i] = sums[i-1] + stones[i-1];

    for(int len = 2; len <=n; len++) {
        for(int left = 1; left <= n - len +1; left++) {
            int right = left + len - 1;
            dp[left][right] = INT_MAX;
            int sum = sums[right] - sums[left-1]; 
            for(int k = left; k<right; k++) {
                dp[left][right] = min(dp[left][right], sum + dp[left][k] + dp[k+1][right]);
            }
        }
    }
    return dp[1][n];
}

int main() {
    vector<int> stones= {6,4,4,6};
    cout << mergeStones(stones) <<endl;
}