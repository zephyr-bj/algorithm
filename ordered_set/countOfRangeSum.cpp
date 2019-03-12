    int countRangeSum(vector<int>& nums, int lower, int upper) {
        long long lowerll = (long long)(lower);
        long long upperll = (long long)(upper);
        multiset<long long>sbin;
        long long x = 0;
        int L = nums.size();
        for(int i=0; i<L; i++){
            x+=(long long)(nums[i]);
            sbin.insert(x);
        }
        int ans = 0;
        long long shift=0;
        for(int i=0; i<L; i++){
            multiset<long long>::iterator ilow=sbin.lower_bound(lowerll);
            multiset<long long>::iterator iupp=sbin.upper_bound(upperll);
            for(multiset<long long>::iterator it=ilow; it!=iupp; it++){
                ans++;
            }
            lowerll+=(long long)(nums[i]);
            upperll+=(long long)(nums[i]);
            shift+=(long long)(nums[i]);
            sbin.erase(sbin.find(shift));  
        }
        return ans;
    }
