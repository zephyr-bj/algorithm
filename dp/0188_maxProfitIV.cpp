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
    /*first figured out a method to use k*2 variables
        int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n<2||k==0)return 0;
        if(k>n/2)k=n/2;
        vector<int>tmp;
        vector<vector<int>>buy(k,tmp);
        vector<vector<int>>sell(k,tmp);
        buy[0].push_back(-prices[0]);
        int ans = 0;
        for(int i=1; i<n; i++){
            for(int j=k-1; j>=0; j--){
                if(buy[j].size()>0){
                    if(sell[j].size()>0){
                        sell[j].push_back(max(sell[j].back(),buy[j].back()+prices[i]));
                    }else{
                        sell[j].push_back(buy[j].back()+prices[i]);
                    }
                    if(sell[j].back()>ans)ans=sell[j].back();
                }
                if(j==0||sell[j-1].size()>0){
                    if(j==0){
                        buy[j].push_back(max(buy[j].back(),-prices[i]));
                    }else{
                        if(buy[j].size()>0){
                            buy[j].push_back(max(sell[j-1].back()-prices[i], buy[j].back()));
                        }else{
                            buy[j].push_back(sell[j-1].back()-prices[i]);
                        }
                    }
                }
            }
        }
        return ans;
    }
    */
