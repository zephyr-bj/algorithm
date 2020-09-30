    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        for(auto x:nums){
            if(nums[abs(x)]>0)
                nums[abs(x)]=-nums[abs(x)];
            else
                return abs(x);
        }
        return 0;
    }
