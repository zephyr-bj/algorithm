    int findMin(vector<int>& nums) {
        int n = nums.size();
        int x = 0; int y = n-1;
        while(x<y){
            int mid = (x+y)/2;
            if(nums[mid]>nums[y])x=mid+1;
            else y=mid;
        }
        return nums[x];
    }
