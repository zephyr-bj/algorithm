    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        int bbuy1 = -prices[0];
        int bsel1 = 0;
        int bbuy2 = INT_MIN;
        int bsel2 = 0;
        for(int i=1; i<n; i++){
            if(bbuy2 > INT_MIN)bsel2 = max(bsel2, bbuy2+prices[i]);
            if(bsel1 > 0)bbuy2 = max(bbuy2, bsel1-prices[i]);
            bsel1 = max(bsel1, bbuy1+prices[i]);
            bbuy1 = max(bbuy1,-prices[i]);
        }
        return max(bsel1, bsel2);
    }
