    void SSTool(int p, int n, vector<int>&nums, vector<int>&path, vector<vector<int>>&ans){
        ans.push_back(path);
        for(int i=p; i<n; i++){
            if(i>p&&nums[i]==nums[i-1])continue;
            path.push_back(nums[i]);
            SSTool(i+1,n,nums,path,ans);
            path.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<int>path;
        vector<vector<int>>ans;
        SSTool(0,nums.size(),nums,path,ans);
        return ans;
    }
