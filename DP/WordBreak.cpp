


/*vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        int n = s.length();
        vector<string> result;
        vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
        
        for(int len=1;len<=n;len++){
            for(int i=0;i<n-len+1;i++){
                int j = i+len-1;
                string temp = word.substr(i,j+1);
                if(wordDict.count(temp)) 
                    dp[i][j] = i;
                else {
                    for(int k = i+1;k<j;k++){
                        
                    }
                }
            }
        }
    }
    */