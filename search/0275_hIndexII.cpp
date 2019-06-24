    int hIndex(vector<int>& citations) {
        int n = citations.size();
        if(n==0)return 0;
        int x = 0; int y=n-1;
        while(x<y){
            int m = (x+y)>>1;
            if(n-m==citations[m])return n-m;
            else if(n-m<citations[m])y=m;
            else if(n-m>citations[m])x=m+1;
        }
        return min(n-x,citations[x]);
    }
