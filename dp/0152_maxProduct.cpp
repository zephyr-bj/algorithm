    // Time O(n), Space O(1)
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n<1)return 0;
        int minP = nums[0];
        int maxP = nums[0];
        int ans = nums[0];
        for(int i=1; i<n; i++){
            if(nums[i]>0){
                minP=min(nums[i],minP*nums[i]);
                maxP=max(nums[i],maxP*nums[i]);
            }else if(nums[i]<0){
                // this temperary variable is important
                int minCP = minP; 
                minP=min(nums[i],maxP*nums[i]);
                maxP=max(nums[i],minCP*nums[i]);
            }else{
                minP=0; maxP=0;
            }
            ans = max(ans,maxP);
        }
        return ans;
    }
    /*
    need two variables, maxP and minP, 
    important is definition: max/min product of the subarray including the ith num
    */
