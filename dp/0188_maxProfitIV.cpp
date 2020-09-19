    
// time O(nk) space O(n), over 500ms
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<int> F(n);
        for(int i=1;i<=min(k, n/2);i++) {
            int tmp=F[0]-prices[0];                     //  init with negative assets
            for(int j=1;j<n;j++){                       
                int x = F[j];                           //  assets before buy
                F[j] = max(tmp+prices[j], F[j-1]);      //  assets after sell, or not sell
                tmp = max(x-prices[j], tmp);            //  assets after buy, or not buy
            }
        }
        return !n ? 0 : F[n-1];
    }
    // time O(nk) space O(k), over 500ms
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        if(k<1)return 0;
        vector<int>buy(k+1,INT_MIN);
        vector<int>sell(k+1,0);
        for(int i=0; i<n; i++){
            for(int j=k; j>0; j--){
                sell[j] = max(sell[j],buy[j]+prices[i]);
                buy[j] = max(buy[j],sell[j-1]-prices[i]);
            }
        }
        return sell[k];
    }
    /*time O(nk), space O(k), 12ms: specail process for k>=n/2*/
       int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        if(k<1)return 0;
        if(k>n/2){
            int ans=0;
            for(int i=1; i<n; i++){
                ans+=max(prices[i]-prices[i-1],0);
            }
            return ans;
        }
        vector<int>buy(k+1,INT_MIN);
        vector<int>sell(k+1,0);
        for(int i=0; i<n; i++){
            for(int j=k; j>0; j--){
                sell[j] = max(sell[j],buy[j]+prices[i]);
                buy[j] = max(buy[j],sell[j-1]-prices[i]);
            }
        }
        return sell[k];
    }
    
