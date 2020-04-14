//bucket sort solution   
//for the bucket sort solution, I'm stuck at a case such as k=5, t=3, nums = {3, 1, 5}
//I'm think the newer but further element, such as 1 will overwrite the older but closer element 3, so 5 has no chance to see 3.
//But this kind of case is not going to happenm, since 1 and 3 will fall in the same bucket and return true, so we do not need 5

// the "getBucketId" function deal with the negative cases. 
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    int n = nums.size();
    if(n<2||k<1||t<0)return false;
    long long w = (long long)(t)+1;
    unordered_map<long long,int>bin;
    for(int i=0; i<n; i++){
        long long x = (long long)(nums[i]);
        if(bin.find(x/w)!=bin.end()&&i-bin[x/w]<=k&&abs(x-nums[bin[x/w]])<=t)return true;
        if(bin.find(x/w-1)!=bin.end()&&i-bin[x/w-1]<=k&&x-nums[bin[x/w-1]]<=t)return true;
        if(bin.find(x/w+1)!=bin.end()&&i-bin[x/w+1]<=k&&nums[bin[x/w+1]]-x<=t)return true;
        bin[x/w]=i;
    }
    return false;
}
// set solution
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<int> window; 
    for (int i = 0; i < nums.size(); i++) {
        if (i > k) window.erase(nums[i-k-1]); 
        auto pos = window.lower_bound(nums[i] - t); //looking for elements larger or equal to (num[i]-t)  
        if (pos != window.end() && *pos - nums[i] <= t) return true;
        window.insert(nums[i]);
    }
    return false;
}
