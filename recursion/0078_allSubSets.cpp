    void SSTool(int p, int n, vector<int>&nums, vector<int>&path, vector<vector<int>>&ans){
        ans.push_back(path);
        for(int i=p; i<n; i++){
            path.push_back(nums[i]);
            SSTool(i+1,n,nums,path,ans);
            path.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>>ans;
        int n = nums.size();
        vector<int>path;
        SSTool(0,n,nums,path,ans);
        return ans;
    }
