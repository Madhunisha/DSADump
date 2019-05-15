#include <iostream>
#include <vector>

using namespace std;


int shortestSuperSeqIter(string& s1, string& s2){
    int m= s1.size(), n=s2.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for(int i=0;i<=m;i++)
        dp[i][0]=i;
    for(int j=0;j<=n;j++)
        dp[0][j]=j;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1]==s2[j-1])
                dp[i][j] = dp[i-1][j-1]+1;
            else
            {
                dp[i][j]=min(dp[i-1][j],dp[i][j-1])+1;
            }
            
        }
    }
    return dp[m][n];
}

int shortestSuperSeqRecur(string& s1, string& s2, int st1, int st2, vector<vector<int>>& dp){
    if(st1>=s1.length())
        return s2.length()-st2;
    if(st2>=s2.length())
        return s1.length()-st1;
    if(dp[st1][st2]!=INT_MAX) return dp[st1][st2];
    if(s1[st1]==s2[st2])
        return dp[st1][st2]=shortestSuperSeqRecur(s1,s2,st1+1,st2+1,dp)+1;
    else
    {
        return dp[st1][st2]=min(shortestSuperSeqRecur(s1,s2,st1+1,st2,dp), shortestSuperSeqRecur(s1,s2,st1,st2+1,dp)) + 1;
    }
    
}

int shortestSuperSeqRecur(string& s1, string& s2){
    int m= s1.size(), n=s2.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,INT_MAX));
    return shortestSuperSeqRecur(s1,s2,0,0,dp);
}

int main() {
    string s1 = "abcf";
    string s2 = "bdcf";
    cout << shortestSuperSeqIter(s1,s2)<<endl;
    cout << shortestSuperSeqRecur(s1,s2)<<endl;
    return 0;
}