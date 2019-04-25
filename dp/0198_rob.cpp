    int rob(vector<int>& nums) {
        int n=nums.size();
        if(n<1)return 0;
        if(n<2)return nums[0];
        vector<int>bin(1,nums[0]);
        bin.push_back(max(nums[0],nums[1]));
        for(int i=2; i<n; i++){
            bin.push_back(max(bin[i-2]+nums[i],bin[i-1]));
        }
        return bin.back();
    }
