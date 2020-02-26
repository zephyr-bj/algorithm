    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for(int i=0; i<n; i++){
            while(nums[i]>0&&nums[i]<n+1&&nums[i]!=nums[nums[i]-1]){
                swap(nums[i],nums[nums[i]-1]);
            }
        }
        for(int i=0; i<n; i++){
            if(nums[i]!=i+1)return i+1;
        }
        return n+1;
    }    
// old way:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        if(n<1)return 1;
        for(int i=0; i<n; i++){
            int k = nums[i]; // the next positive to check
            while(k>0&&k<=n&&nums[k-1]!=k){
                int t = nums[k-1];
                nums[k-1]=k;
                k=t;
            }
        }
        for(int i=0; i<n; i++){
            if(nums[i]!=i+1)return i+1;
        }
        return n+1;
    }
