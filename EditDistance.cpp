#include <iostream>
#include <vector>

using namespace std;

int editDistanceIter(string s1, string s2){
    int m=s1.length(),n=s2.length();
    vector<vector<int>> dp(m+1,vector<int>(n,0));
    for(int i=1;i<=m;i++)
        dp[i][0]=i;
    
    for(int j=1;j<=n;j++)
        dp[0][j]=j;

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1]==s2[j-1])
                dp[i][j]=dp[i-1][j-1];
            else
            {
                dp[i][j]=min(dp[i][j-1],dp[i-1][j])+1;
            }
            
        }
    }
    return dp[m][n];

}
int main() {
    string s1 = "passport";
    string s2 = "ppsspt";
    cout << editDistanceIter(s1,s2)<<endl;
    return 0;
}