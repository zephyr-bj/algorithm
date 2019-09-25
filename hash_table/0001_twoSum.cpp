    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>bin;
        vector<int>ans;
        int n = nums.size();
        for(int i=0; i<n; i++){
            if(bin.find(nums[i])==bin.end())bin[target-nums[i]]=i;
            else{
                ans.push_back(bin[nums[i]]);
                ans.push_back(i);
                break;
            }
        }
        return ans;
    }
