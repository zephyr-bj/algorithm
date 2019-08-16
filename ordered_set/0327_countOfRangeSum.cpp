
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        multiset<long long>bin;
        bin.insert(0);
        long long sum=0;
        int ans=0;
        int n = nums.size();
        for(int i=0; i<n; i++){
            sum+=nums[i];
            multiset<long long>::iterator left = bin.lower_bound(sum-(long long)(upper));
            //use upper_bound here, since we do not want to touch it in the loop
            multiset<long long>::iterator right = bin.upper_bound(sum-(long long)(lower));
            for(multiset<long long>::iterator it=left; it!=bin.end()&&it!=right; it++)
                if(*it<=sum-lower && *it>=sum-upper)ans++;
            bin.insert(sum);
        }
        return ans;
    }
