    // time O(n^2), space O(n^2)
    // how to cut the branches: do not need to check every element in the array, just check the larget element. 
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if(n<1)return vector<int>({});
        sort(nums.begin(),nums.end());
        vector<vector<int>>lds(n,vector<int>({}));
        lds[0].push_back(nums[0]);
        int ans = 0;
        for(int i=1; i<n; i++){
            int x = -1;
            for(int j=0; j<i; j++){
                if(nums[i]%lds[j].back()==0){
                    if(x==-1||lds[j].size()>lds[x].size())x = j;
                }
            }
            if(x==-1){
                lds[i].push_back(nums[i]);
            }else{
                lds[i]=lds[x];
                lds[i].push_back(nums[i]);
            }
            if(lds[i].size()>lds[ans].size())ans=i;
        }
        return lds[ans];
    }
