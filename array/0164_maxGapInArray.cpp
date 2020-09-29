    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n<2)return 0;
        int lb = nums[0];
        int ub = nums[0];
        for(int i=1; i<n; i++){
            if(nums[i]>ub)ub=nums[i];
            if(nums[i]<lb)lb=nums[i];
        }
        if(lb==ub)return 0;
        int wide = max((ub-lb)/(n-1),1);
        int sz = (ub-lb)/wide+1;
        vector<int>lbin(sz,INT_MAX);
        vector<int>ubin(sz,INT_MIN);
        for(int i=0; i<n; i++){
            int idx = (nums[i]-lb)/wide;
            if(nums[i]<lbin[idx])lbin[idx]=nums[i];
            if(nums[i]>ubin[idx])ubin[idx]=nums[i];
        }
        int ans =0;
        int j=0;
        for(int i=1; i<sz; i++){
            if(lbin[i]==INT_MAX||ubin[i]==INT_MIN)continue;
            ans = max(ans,lbin[i]-ubin[j]);
            j=i;
        }
        return ans;
    }
/*
The lower bound of the max gap is (ub-lb)/(n-1) <== divide the range evenly, max gap must between the buckets
to guarantee measure the gap between two neighboring elements, we evaluate lbin[i]-ubin[pre]
*/
// similarly
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n<2)return 0;
        int a = nums[0];
        int b = nums[0];
        for(auto x:nums){
            if(x<a)a=x;
            if(x>b)b=x;
        }
        int span = (b-a)/(n-1)+1;//+1: to prevent the b fall out of the highest bin
                                 //    to prevent span turn out to be zero, when b close to a.
        vector<int>A(n-1,INT_MAX);
        vector<int>B(n-1,INT_MIN);
        for(int i=0; i<n; i++){
            int idx = (nums[i]-a)/span;
            if(nums[i]<A[idx])A[idx]=nums[i];
            if(nums[i]>B[idx])B[idx]=nums[i];
        }
        int ans = min(abs(nums[0]-nums[1]),B[0]-A[0]);
        int last = B[0];
        for(int i=1; i<n-1; i++){
            if(B[i]==INT_MIN)continue;
            ans = max(ans,B[i]-A[i]);
            ans = max(ans,A[i]-last);
            last = B[i];
        }
        return ans;
    }
