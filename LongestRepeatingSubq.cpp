#include <iostream>
#include <vector>

using namespace std;
int longestRepeatSubqRecur(string s1, string s2, vector<vector<int>>& dp, int st1, int st2){
    if(st1 >=s1.length() || st2 >= s2.length()) return 0;
    if(dp[st1][st2]!=-1) return dp[st1][st2];
    if(s1[st1] == s2[st2]&&st1!=st2)
        return dp[st1][st2] = 1 + longestRepeatSubqRecur(s1,s2,dp,st1+1,st2+1);
    return dp[st1][st2]=max(longestRepeatSubqRecur(s1,s2,dp,st1+1,st2),longestRepeatSubqRecur(s1,s2,dp,st1,st2+1));
}
int longestRepeatSubqRecur(string s1, string s2){
    vector<vector<int>> dp(s1.length(),vector<int>(s2.length(),-1));
    return longestRepeatSubqRecur(s1,s2,dp,0, 0);
}

int longestRepeatSubqIter(string s1, string s2){
    int m = s1.length(), n= s2.length();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    int maxLength=0;
    for(int i =1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1] == s2[j-1] && i!=j){
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
            maxLength=max(maxLength,dp[i][j]);
        }
    }
    return maxLength;
}

int main() {
    string s1 = "aabdbcec";
    string s2 = "ppsspt";
    cout << longestRepeatSubqRecur(s1,s1)<<endl;
    cout << longestRepeatSubqIter(s1,s1)<<endl;
    return 0;
}