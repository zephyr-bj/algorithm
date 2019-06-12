    int lengthOfLIS(vector<int>& nums) {
        set<int>bin;
        int n = nums.size();
        for(int i=0; i<n; i++){
            set<int>::iterator it = bin.lower_bound(nums[i]);
            if(it!=bin.end())bin.erase(it);
            bin.insert(nums[i]);
        }
        return bin.size();
    }
/*
can not use stack rising sequence trick
*/
