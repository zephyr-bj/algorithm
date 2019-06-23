    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int>ans(2,-1);
        int L=nums.size();
        if(L==0)return ans;
        int x=0; int y=L-1;
        while(x<y){
            int k=(x+y)>>1;
            if(target-0.5>nums[k])x=k+1;
            else y=k-1;
        }
        if(nums[x]==target)ans[0]=x;
        else if(x<L-1&&nums[x+1]==target)ans[0]=x+1;
        x=0; y=L-1;
        while(x<y){
            int k=(x+y)>>1;
            if(target+0.5>nums[k])x=k+1;
            else y=k-1;
        }
        if(nums[x]==target)ans[1]=x;
        else if(x>=1&&nums[x-1]==target)ans[1]=x-1;
        return ans;
    }
