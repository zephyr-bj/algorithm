    //method 1: always keep the order, pass vector by values
    void PMTool(vector<int> nums, int p, vector<vector<int>>&ans){
        if(p==nums.size()-1){
            ans.push_back(nums); return;
        }
        for(int i = p; i<nums.size(); i++){
            if(i!=p&&nums[i]==nums[p])continue;
            swap(nums[p],nums[i]);
            PMTool(nums,p+1,ans);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>>ans;
        PMTool(nums,0,ans);
        return ans;
    }

    //method 2: do not keep order, only swap unswapped elements, pass vector by reference
    void PMTool2(vector<int> &nums, int p, vector<vector<int>>&ans){
        if(p==nums.size()-1){
            ans.push_back(nums); return;
        }
        unordered_set<int>bin;
        for(int i = p; i<nums.size(); i++){
            if(bin.count(nums[i])==0){
                swap(nums[p],nums[i]);
                PMTool(nums,p+1,ans);
                swap(nums[p],nums[i]);
                bin.insert(nums[i]);
            }
        }
    }
    vector<vector<int>> permuteUnique2(vector<int>& nums) {
        vector<vector<int>>ans;
        PMTool2(nums,0,ans);
        return ans;
    }
