    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int,int>bin;
        int n = nums.size();
        for(int i=0; i<n; i++){
            if(bin.find(nums[i])==bin.end()){
                bin[nums[i]]=i;
            }else{
                if(i-bin[nums[i]]<=k)return true;
                else bin[nums[i]]=i;
            }
        }
        return false;
    }
