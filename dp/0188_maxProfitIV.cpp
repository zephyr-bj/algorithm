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
        if(n<2||k<1)return 0;
        vector<int>A(min(n,2*k),0);
        for(int x=0; x<A.size(); x+=2)A[x]=INT_MIN;
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int j=1; j<min(i+1,2*k); j++){
                if(j%2){ //sell
                    A[j]=max(A[j],A[j-1]+prices[i]);
                    ans = max(ans,A[j]);
                }else{   //buy
                    A[j]=max(A[j],A[j-1]-prices[i]);
                }
            }
            A[0]=max(A[0],-prices[i]);
        }
        return ans;
    }
    /*time O(nk), space O(k), 4ms: specail process for k>=n/2
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        if(k>=n/2){
            int bb = -prices[0];
            int bs = 0;
            for(int i=1; i<n; i++){
                int cbs = bs;
                bs = max(bs, bb+prices[i]);
                bb = max(bb, cbs-prices[i]);
            }
            return bs;
        }
        vector<int>bbuy(k,INT_MIN);
        vector<int>bsel(k,0);
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int t=k; t>0; t--){
                if(i>2*t-2&&bbuy[t-1]>INT_MIN)bsel[t-1]=max(bsel[t-1],bbuy[t-1]+prices[i]);
                if(i>2*t-3){
                    if(t<2)bbuy[t-1]=max(bbuy[t-1],-prices[i]);
                    else if(bsel[t-2]>0)bbuy[t-1]=max(bbuy[t-1],bsel[t-2]-prices[i]);
                }
                ans = max(ans,bsel[t-1]);
            }
        }
        return ans;
    }
    */
