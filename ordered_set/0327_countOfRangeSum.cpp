
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        multiset<long long>bin;
        int n = nums.size();
        long long sum=0;
        bin.insert(0);
        int ans=0;
        for(int i=0; i<n; i++){
            sum+=nums[i];
            multiset<long long>::iterator lb = bin.lower_bound(sum - (long long)(upper));
            multiset<long long>::iterator ub = bin.upper_bound(sum - (long long)(lower));
            if(ub==bin.begin()&&((sum-(long long)(lower))<*ub)){
                bin.insert(sum);continue;
            }
            if(lb==bin.end()){
                bin.insert(sum);continue;
            }
            int cnt=0;
            for(multiset<long long>::iterator it=lb; it!=ub; it++)cnt++;
            ans+=cnt;
            bin.insert(sum);
        }
        return ans;
    }
/*
use upper bound, so we cover the equal elements case
*/
