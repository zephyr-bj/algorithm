    int jump(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        int ans=0;
        while(i<n-1){
            int x=0;
            int s=0;
            if(i+nums[i]>=n-1)return ans+1;
            for(int t=1; i+t<n&&t<=nums[i]; t++){
                if(t+nums[i+t]>s){
                    s=t+nums[i+t];x=t;
                }
            }
            ans++;
            i+=x;
        }
        return ans;
    }
