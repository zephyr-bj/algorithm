
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

// a merge sort algorithm, 
// theoretically, this is more clearly O(Nlog(N)), since the loop in util function is still O(N)
// practically, it may takes longer, and uses more memory
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long>sum(n+1,0);
        for(int i=1; i<=n; i++)sum[i]=sum[i-1]+nums[i-1];
        return countUtil(sum,0,n,lower,upper);
    }
    int countUtil(vector<long>&sum, int x, int y, int lower, int upper){
        if(x>=y)return 0;
        int mid = (x+y)/2;
        int cnt=countUtil(sum,x,mid,lower,upper)+countUtil(sum,mid+1,y,lower,upper);
        int i=mid+1;
        int j=mid+1;
        int k=mid+1;
        vector<int>mergeBin;
        for(int left=x; left<=mid; left++){
            while(i<=y && sum[i]-sum[left]<lower)i++;
            while(j<=y && sum[j]-sum[left]<=upper)j++;
            cnt+=(j-i);
            while(k<=y && sum[k]<sum[left])mergeBin.push_back(sum[k++]);
            mergeBin.push_back(sum[left]);
        }
        for(int s=0; s<mergeBin.size(); s++)sum[x+s]=mergeBin[s];
        return cnt;
    }
