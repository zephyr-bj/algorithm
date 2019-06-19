    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        if(n<1)return n;
        int i=0; 
        int l=n;
        for(int j=0; j<n; j++){
            nums[i]=nums[j];
            if(nums[j]!=val)i++;
            else l--;
        }
        return l;
    }
