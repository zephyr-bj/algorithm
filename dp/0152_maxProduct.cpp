    // Time O(n), Space O(1)
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n<1)return 0;
        int a = nums[0];
        int b = nums[0];
        int ans = nums[0];
        for(int i=1;i<n;i++){
            int x = min(nums[i],min(a*nums[i],b*nums[i]));
            int y = max(nums[i],max(a*nums[i],b*nums[i]));
            a = x;
            b = y;
            ans = max(ans,b);
        }
        return ans;
    }
    /*
    need two variables, maxP and minP, 
    important is definition: max/min product of the subarray including the ith num
    */
