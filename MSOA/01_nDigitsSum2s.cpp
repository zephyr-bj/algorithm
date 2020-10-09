long countTool(int n, int sum, vector<vector<int>>&lookup){
    if(n==0) return sum==0;
    if(sum==0) return 1;
    if(lookup[n][sum]!=-1)return lookup[n][sum];
    
    long ans=0;
    for(int i=0; i<=9; i++)
        if(sum-i>=0)
            ans += countTool(n-1,sum-i);
    return lookup[n][sum]=ans;
}

long nDigitsSum2s(int n, int s){
    vector<vector<int>>lookup(n+1,vector<int>(s+1,-1));
    long ans = 0;
    for(int i=1; i<=9; i++)
        if(sum-i>=0)
            ans += countTool(n-1, sum-i, lookup);
    return ans;
}
            
