vector<vector<int>>partition(vector<int>&nums, int n){
    int sz = nums.size();
    vector<int>sum(n,0);
    auto my_cmp = [&sum](int a, int b) {return sum[a] >= sum[b];};
    priority_queue<int, vector<int>, decltype(my_cmp)>bin;
    vector<vector<int>>ans(n,vector<int>());
    for(int i=0; i<n; i++)bin.push(i);
    for(int i=n-1; i>=0; i--){
        int x = bin.top(); bin.pop();
        ans[x].push_back(nums[i]);
        sum[x]+=nums[i];
        bin.push(x);
    }
    return ans;
}
        
