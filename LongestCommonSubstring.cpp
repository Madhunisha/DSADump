#include <iostream>
#include <vector>
using namespace std;

int longestCommonSubIter(string s1,string s2){
    vector<vector<int>> dp(s1.length()+1,vector<int>(s2.length()+1,0));
    int maxLength=0;
    for(int i=1;i<s1.length();i++){
        for(int j=1;j<s2.length();j++){
            if(s1[i-1]==s2[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
                maxLength = max(maxLength,dp[i][j]);
            }
        }
    }
    return maxLength;
}
int main() {
    string s1 = "abdca";
    string s2 = "cbda";
    cout << longestCommonSubIter(s1,s2)<<endl;
    return 0;
}