    int kthSmallest(vector<vector<int>>& a, int k) {
        int l,h,m,ans,n;
        n=a.size();
        l=a[0][0];
        h=a[n-1][n-1];
        while(l<=h){
            m=l+(h-l)/2;
            int c=0;
            for(int i=0;i<n;i++)
                c+=upper_bound(begin(a[i]),end(a[i]),m)-begin(a[i]);
            if(c<k)
                l=m+1;
            else{
                ans=m;
                h=m-1;
            }
        }
        return ans;
    }
