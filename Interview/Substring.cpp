#include <iostream>
#include <string>
#include <vector>

using namespace std;

// KMP Algorithm
int findSubstr(string& s1, string& s2){
    int m=s1.size(), n=s2.size();
    vector<int> pos(s2.size());
    int j=0,i=1;
    while(i<n){
        if(s2[i]==s2[j]){
            pos[i++]=++j;
        } else {
            if(j!=0) j = pos[j-1];
            else i++;
        }
    }
    
    i=j=0;
    while(i<m){
        if(s1[i] == s2[j]){
            i++,j++;
            if(j==n) return i-j;
        } else {
            if(j!=0)
                j=pos[j-1];
            else i++;
        }
    }

    return -1;
}


int main() {
    string s1="abxabcabcaby";
    string s2 = "abcaby";
    string s3 = "aabaabaaa";
    cout << findSubstr(s1,s2);
    cout<<endl;
    return 0;
}