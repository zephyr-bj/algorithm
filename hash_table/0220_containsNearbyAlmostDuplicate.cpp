//bucket sort solution   
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(t<0)return false;
        unordered_map<int,int>bin;
        int n = nums.size();
        for(int i=0; i<n; i++){
            int target = t>0?nums[i]/t:nums[i];
            int r = t>0?nums[i]%t:0;
            if(bin.find(target)!=bin.end()){
                if(abs(r-bin[target])<=t)return true;
            }else if(t>0){
                if(bin.find(target-1)!=bin.end()){
                    if(r<=bin[target-1])return true;
                }
                if(bin.find(target+1)!=bin.end()){
                    if(r>=bin[target+1])return true;
                }
            }
            bin[target]=r;
            if(i>=k)bin.erase(t>0?nums[i-k]/t:nums[i-k]);
        }
        return false;
    }
// set solution
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        multiset<long long>bin;
        if(k<1&&t<0)return false;
        int n = nums.size();
        for(int i=0; i<n; i++){
            if(i>k)bin.erase(bin.find(nums[i-k-1]));
            multiset<long long>::iterator it = bin.lower_bound((long long)nums[i]-(long long)t);
            if(it!=bin.end()&&abs(nums[i]-(*it))<=t)return true;
            bin.insert(nums[i]);
        }
        return false;
    }
