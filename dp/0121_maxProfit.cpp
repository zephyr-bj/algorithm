    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        int p = -prices[0];//the lowest price I find by far
        int ans = 0;
        for(int i=1; i<n; i++){
            ans = max(ans, prices[i]+p);
            p=max(p,-prices[i]);
        }
        return ans;
    }
