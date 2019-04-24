    int maxCoins(vector<int>& nums) {
        int n=nums.size();
        if(n==0)return 0;
        vector<int>balloons(1,1);
        for(int i=0; i<n; i++)balloons.push_back(nums[i]);
        balloons.push_back(1);
        vector<int>tmp(n+2,0);
        vector<vector<int>>dp(n+2,tmp);
        for(int len=3; len<=n+2; len++){
            for(int l=0; l<=n+2-len; l++){
                int r = l+len-1;
                for(int k=l+1; k<r; k++){
                    int x = dp[l][k]+dp[k][r]+balloons[l]*balloons[k]*balloons[r];
                    if(dp[l][r]<x)dp[l][r]=x;
                }
            }
        }
        return dp[0][n+1];
    }
