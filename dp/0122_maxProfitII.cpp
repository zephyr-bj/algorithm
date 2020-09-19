    /*solution1*/
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        int ans = 0;
        for(int i=1; i<n; i++){
            ans += max(prices[i]-prices[i-1],0);
        }
        return ans;
    }
    /*solution2*/
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        int bbuy = -prices[0];
        int bsel = 0;
        for(int i=1; i<n; i++){
            int tbbuy = bsel - prices[i];
            int tbsel = bbuy + prices[i];
            bsel = max(bsel,tbsel);
            bbuy = max(bbuy,tbbuy);
        }
        return bsel;
    }
