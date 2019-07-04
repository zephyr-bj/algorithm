    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int>bin;
        for(int i=0; i<nums.size(); i++){
            if(bin.find(nums[i])!=bin.end())return true;
            else bin.insert(nums[i]);
        }
        return false;
    }
