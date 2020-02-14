    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        while(i<n-1){
            int x=0;
            int s=0;
            for(int t=1; i+t<n&&t<=nums[i]; t++){
                if(t+nums[i+t]>s){
                    s=t+nums[i+t];x=t;
                }
            }
            if(x<1)return false;
            i+=x;
        }
        return true;
    }
