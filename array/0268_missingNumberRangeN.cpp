    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(n);
        for(int i=0; i<n; i++){
            nums[abs(nums[i])]=-nums[abs(nums[i])];
        }
        int ans =0;
        for(int i=0; i<=n; i++){
            if(nums[i]>0)return i;
            else if(nums[i]==0)ans=i;
        }
        return ans;
    }
    // another solution
    /*
        int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        while(i<n){
            if(nums[i]!=i){
                int j = nums[i];
                while(nums[j]!=j&&j!=n){
                    int tmp = nums[j];
                    nums[j]=j;
                    j=tmp;
                }
            }
            i++;
        }
        for(int i=0; i<n; i++){
            if(nums[i]!=i)return i;
        }
        return n;
    }
    */
