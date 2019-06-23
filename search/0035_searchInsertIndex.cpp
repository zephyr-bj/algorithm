    int searchInsert(vector<int>& nums, int target) {
        int L = nums.size();
        if(L==0)return 0;
        int x=0; int y=L-1;
        while(x<y){
            int k=(x+y)>>1;
            if(target==nums[k])return k;
            else if(target<nums[k]) y=k-1;
            else x=k+1;
        }
        return target>nums[x]?x+1:x;
    }
