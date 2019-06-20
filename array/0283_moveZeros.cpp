    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        if(n<2)return;
        int i=0;
        int l=n;
        for(int j=0; j<n; j++){
            nums[i]=nums[j];
            if(nums[j]==0)l--;
            else i++;
        }
        for(int j=l; j<n; j++)nums[j]=0;
    }
