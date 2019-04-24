    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n = nums.size();
        vector<int>ans;
        if(n<1)return ans;
        vector<int>tmp(1,1);
        tmp.push_back(-1);//[0] for size, [1] for pointer
        vector<vector<int>>bin(1,tmp);
        int sz=1; int idx=0;
        for(int i=1; i<n; i++){
            int l=1;
            int k=-1;
            for(int j=i-1; j>=0; j--){
                if(nums[i]%nums[j]==0&&l<bin[j][0]+1){
                    l=bin[j][0]+1;
                    k=j;
                }
            }
            vector<int>tmp(1,l);
            tmp.push_back(k);
            bin.push_back(tmp);
            if(l>sz){
                sz=l; idx=i;
            }
        }
        int it=bin[idx][1];
        ans.push_back(nums[idx]);
        while(it!=-1){
            ans.push_back(nums[it]);
            it=bin[it][1];
        }
        return ans;
    }
