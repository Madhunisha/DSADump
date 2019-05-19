#include <iostream>
#include <vector>

using namespace std;
// Iterative DP solution
int LISWithMaxSumIter(vector<int>& nums) {
        int n = nums.size();
        if(n==0 || n==1) return n;
        vector<int> dp(n);
        for(int i=0;i<n;i++)
        dp[i]=nums[i];

        int maxVal=nums[0];
        for(int i=1;i<n;i++){
            int temp = dp[i];
            for(int j=0;j<i;j++){
                if(nums[i]> nums[j] && dp[i]<=(dp[j]+temp)) {
                    dp[i]=temp+dp[j];
                    maxVal = max(maxVal,dp[i]);
                }
            }
        }
        return maxVal;
}
int main() {
    vector<int> vec = {1,3,8,4,14,6,14,1,9,4,13,3,11,17,29};
    cout << LISWithMaxSumIter(vec)<<endl;
    return 0;
}