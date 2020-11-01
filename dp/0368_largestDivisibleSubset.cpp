    // time O(n^2), space O(n^2)
    // how to cut the branches: do not need to check every element in the array, just check the larget element. 
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        if(n<1)return vector<int>();
        vector<vector<int>>lds(1,vector<int>({1,-1}));
        int idx = 0; int L = 1;
        for(int i=1; i<n; i++){
            int l = 1;
            int k = -1;
            for(int j=0; j<i; j++){
                if((nums[i]%nums[j]==0) && (l<lds[j][0]+1)){
                    l=lds[j][0]+1;
                    k=j;
                }
            }
            vector<int>tmp({l,k});
            lds.push_back(tmp);
            if(l>L){
                idx = i; L = l;
            }
        }
        vector<int>ans;
        while(idx!=-1){
            ans.push_back(nums[idx]);
            idx=lds[idx][1];
        }
        return ans;
    }
