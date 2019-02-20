    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int>buy(n+1,0);
        buy[0]=INT_MIN;
        vector<int>sell(n+2,0);
        for(int i=0; i<n; i++){
            int j=i+2;
            int k=i+1;
            int prof=sell[j-2]-prices[i];
            if(prof>buy[k-1])buy[k]=prof;
            else buy[k]=buy[k-1];
            prof=buy[k-1]+prices[i];
            if(prof>sell[j-1])sell[j]=prof;
            else sell[j]=sell[j-1];
        }
        return sell.back();
    }
