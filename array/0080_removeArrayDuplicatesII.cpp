    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n<3)return n;
        int i=1;
        int l=n;
        for(int j=2; j<n; j++){
            if(nums[j]==nums[i]&&nums[j]==nums[i-1])l--;
            else i++;
            nums[i]=nums[j];
        }
        return l;
    }
