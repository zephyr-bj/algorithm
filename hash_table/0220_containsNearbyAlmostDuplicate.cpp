//bucket sort solution   
//for the bucket sort solution, I'm stuck at a case such as k=5, t=3, nums = {3, 1, 5}
//I'm think the newer but further element, such as 1 will overwrite the older but closer element 3, so 5 has no chance to see 3.
//But this kind of case is not going to happenm, since 1 and 3 will fall in the same bucket and return true, so we do not need 5

// the "getBucketId" function deal with the negative cases. 
long long getBucketId(long long i, long long w) {
    return i < 0 ? (i + 1) / w - 1 : i / w;
}
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    int n = nums.size();
    if (n < 2 || k < 1 || t < 0){
        return false;
    }
    unordered_map<long long, long long> buckets;
    long long width = (long long)t + 1;
    for (int i = 0; i < n; i++){
        long long id = getBucketId(nums[i], width);
        if (buckets.find(id) != buckets.end()){
            return true;
        }
        if ((buckets.find(id - 1) != buckets.end() && nums[i] - buckets[id - 1] < width)) return true;
        if ((buckets.find(id + 1) != buckets.end() && buckets[id + 1] - nums[i] < width)) return true;

        buckets[id] = nums[i];
        if (i >= k){
            buckets.erase(getBucketId(nums[i - k], width));
        }
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
