    int findMin(vector<int>& nums) {
        int n = nums.size();
        int i=0; int j=n-1;
        while(j>0&&nums[j]==nums[j-1])j--;
        while(i<n-1&&nums[i]==nums[j])i++;
        while(i<j){
            int mid = (i+j)>>1;
            if(nums[mid]>nums[j])i=mid+1;
            else j=mid;
        }
        return nums[i];
    }
