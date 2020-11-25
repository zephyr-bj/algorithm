//method 0: 
    void perm(vector<int>&nums, int p, vector<vector<int>>&ans){
        if(p==nums.size()-1){
            ans.push_back(nums); return;
        }
        for(int i=p; i<nums.size(); i++){
            if(i>p && nums[i] == nums[p])continue;
            swap(nums[p],nums[i]);
            perm(nums,p+1,ans);
        }
        for(int i=nums.size()-1; i>=p; i--){
            swap(nums[p],nums[i]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>>ans;
        perm(nums,0,ans);
        return ans;
    }
//method 2: DFS, use visted array, NO pass by value, NO local visited bin. 
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>>jar;
        vector<int>candy;
        vector<int>visited(nums.size(),0);
        PMTool(nums,visited,candy,jar);
        return jar;
    }
    void PMTool(vector<int>&nums, vector<int>&visited, vector<int>&candy, vector<vector<int>>&jar){
        int n = nums.size();
        if(candy.size()==n){
            jar.push_back(candy);
            return;
        }
        for(int i=0; i<n; i++){
            if(visited[i])continue;
            //nums[i]==nums[i-1] says NOT place same number at the same position (or DFS level)
            //!visited[i-1] says EXCEPT for nums[i-1] was visited at other position (visited in the same level have been cleared by back tracking)
            if(i>0&&nums[i]==nums[i-1]&&(!visited[i-1]))continue;
            visited[i]=1;
            candy.push_back(nums[i]);
            PMTool(nums,visited,candy,jar);
            candy.pop_back();
            visited[i]=0;
        }
    }


    //method 3: always keep the order, pass vector by values
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

    //method 4: do not keep order, only swap unswapped elements, pass vector by reference
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
