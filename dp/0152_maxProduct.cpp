    int maxProduct(vector<int>& nums) {
        int n=nums.size();
        int i=0; 
        while(i<n&&nums[i]==0)i++;
        long long ans=i<n?nums[i]:0;
        long long maxP=i<n?nums[i]:0;
        long long minP=i<n?nums[i]:0;
        i++;
        while(i<n){
            if(nums[i]==0){
                if(i<n-1){
                    maxP=nums[i+1]; 
                    minP=nums[i+1];
                }
                if(ans<0)ans=0;
                i++;
            }else {
                long long n1=maxP*nums[i];
                long long n2=minP*nums[i];
                maxP=nums[i];
                if(maxP<n1)maxP=n1;
                if(maxP<n2)maxP=n2;
                minP=nums[i];
                if(minP>n1)minP=n1;
                if(minP>n2)minP=n2;
            }
            if(ans<maxP)ans=maxP;
            i++;
        }
        return (int)(ans);
    }
    /*
    need to variables, maxP and minP, 
    important is definition: max/min product of the subarray including the ith num
    */
