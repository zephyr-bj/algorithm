    int minSubArrayLen(int s, vector<int>& nums) {
        int L = nums.size();
        if(L<1)return 0;
        int ans = L+1;
        int p=0; int q=0; int sum=0;
        while(q<L){
            sum+=nums[q];
            while(sum-nums[p]>=s){
                sum-=nums[p++];
            }
            if(sum>=s&&q-p+1<ans)ans=q-p+1;
            q++;
        }
        return ((ans>L) ? 0 : ans);
    }
