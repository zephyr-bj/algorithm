    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n<2)return n;
        int i=0; 
        int l=n;
        for(int j=1; j<n; j++){
            if(nums[i]!=nums[j])i++;
            else l--;
            nums[i]=nums[j];
        }
        return l;
    }
