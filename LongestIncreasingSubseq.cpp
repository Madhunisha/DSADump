#include <iostream>
#include <vector>

using namespace std;
// Iterative DP solution
int lengthOfLISIter(vector<int>& nums) {
        int n = nums.size();
        if(n==0 || n==1) return n;
        vector<int> dp(n,1);
        int maxVal=1;
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[i]> nums[j] && dp[i]<=dp[j]) {
                    dp[i]=1+dp[j];
                    maxVal = max(maxVal,dp[i]);
                }
            }
        }
        return maxVal;
}

int main() {
    vector<int> vec = {1,3,6,7,9,4,10,5,6};
    cout << lengthOfLISIter(vec)<<endl;
    return 0;
}