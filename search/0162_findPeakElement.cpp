    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int a = 0; int b = n-1;
        while(a<b){
            int m = (a+b)/2;
            if(nums[m]<nums[m+1]){
                a = m+1;
            }else{
                b = m;
            }
        }
        return a;
    }
