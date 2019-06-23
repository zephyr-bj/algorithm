    int minIdx(vector<int>& nums){
        int n = nums.size();
        int x = 0; int y = n-1;
        while(y>0&&nums[y]==nums[y-1])y--;
        while(x<n-1&&nums[x]==nums[y])x++;
        while(x<y){
            int mid = (x+y)>>1;
            if(nums[mid]>nums[y])x=mid+1;
            else y=mid;
        }
        return x;
    }
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        if(n<1)return false;
        int rot = minIdx(nums);
        int x =0; int y=n-1;
        while(x<=y){
            int mid = (x+y)>>1;
            int realMid = (mid+rot)%n;
            if(nums[realMid]==target)return true;
            else if(nums[realMid]>target)y=mid-1;
            else x=mid+1;
        }
        return false;
    }
