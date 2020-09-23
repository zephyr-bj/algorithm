    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int i = 0; int j=n-1;
        while(i<j){
            int m = (i+j)/2;
            bool peak = false;
            if(m==0){
                if(nums[m]>nums[m+1])return 0;
                else i=m+1;
            }else if(m==n-1){
                if(nums[m]>nums[m-1])return n-1;
                else j=m-1;
            }else{
                if(nums[m]>nums[m-1]&&nums[m]>nums[m+1])return m;
                else if(nums[m]>nums[m-1])i=m+1;
                else j=m-1;
            } 
        }
        return i;
    }
