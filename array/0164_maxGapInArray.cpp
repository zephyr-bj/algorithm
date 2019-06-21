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
