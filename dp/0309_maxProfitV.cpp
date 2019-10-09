    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        if(n<2)return 0;
        vector<int>sell(1,0);          //maxProfit of a sequence ending with sell until day i;
        vector<int>buy(1,-prices[0]);  //maxProfit of a sequence ending with buy until day i;
        sell.push_back(max(0,buy[0]+prices[1]));
        buy.push_back(max(buy[0],-prices[1]));
        for(int i=2; i<n; i++){
            buy.push_back(max(sell[i-2]-prices[i], buy[i-1]));
            sell.push_back(max(buy[i-1]+prices[i], sell[i-1]));
        }
        return sell.back();
    }
//time O(n), space O(1)
    int maxProfitII(vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        int bbuy=-prices[0];
        int bsel=0;
        int bselcd=0;
        for(int i=1; i<n; i++){                 
            int p = bbuy+prices[i];            
            bbuy=max(bbuy,bselcd-prices[i]); 
            bselcd=max(bselcd,bsel);         
            bsel=max(bsel,p); 
        }
        return bsel;
    }
