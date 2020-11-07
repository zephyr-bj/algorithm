    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int>ans(2,-1);
        int a = 0; int b = n;
        while(a<b){
            int m = a+(b-a)/2;
            if(nums[m]<target)a=m+1;
            else b=m;
        }
        if(a>=n || nums[a] != target)return ans;
        ans[0]=a;
        
        a = 0; b=n;
        while(a<b){
            int m = a+(b-a)/2;
            if(nums[m]<=target)a=m+1;
            else b=m;
        }
        ans[1]=a-1;

        return ans;
    }
