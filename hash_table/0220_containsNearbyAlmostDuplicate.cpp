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
    //12ms
    //28ms solution below
        bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(k<1||t<0)return false;
        unordered_map<int,vector<int>>bin;
        int n = nums.size();
        for(int i=0; i<n; i++){
            int target = t>0?nums[i]/t:nums[i];
            int r = t>0?nums[i]%t:0;
            if(bin.find(target)!=bin.end()){
                if(i-bin[target][0]<=k&&abs(r-bin[target][1])<=t)return true;
            }
            if(t>0&&bin.find(target-1)!=bin.end()){
                if(i-bin[target-1][0]<=k&&r<=bin[target-1][1])return true;
            }
            if(t>0&&bin.find(target+1)!=bin.end()){
                if(i-bin[target+1][0]<=k&&r>=bin[target+1][1])return true;
            }
            vector<int>tmp(1,i); 
            tmp.push_back(r);
            bin[target]=tmp;
            if(i>=k)bin.erase(t>0?nums[i-k]/t:nums[i-k]);
        }
        return false;
    }
