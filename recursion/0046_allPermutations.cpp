    void PMTool(vector<int>&nums, int p, vector<vector<int>>&ans){
        if(p==nums.size()-1){
            ans.push_back(nums);return;
        }
        for(int i=p; i<nums.size(); i++){
            swap(nums[p],nums[i]);
            PMTool(nums,p+1,ans);
            swap(nums[p],nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>ans;
        PMTool(nums,0,ans);
        return ans;
    }
