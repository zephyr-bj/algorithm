    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if(k==0||n<2||n==k)return;
        k = k%n;
        if(n<1)return;
        int i = 0;
        int x = nums[i];
        int shift=0;
        for(int j=0; j<n; j++){
            int t = (i+k)%n;
            int y = nums[t];
            nums[t]=x;
            if(t==shift){//for the n%k == 0 case
                shift++;
                t=shift;
                y=nums[t];
            }
            i=t;
            x=y;
        }
    }
