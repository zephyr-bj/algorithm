    vector<int> maxNumber(vector<int>& nums, int k){
        vector<int> ans;                
        for (int i = 0; i < nums.size(); ++i) {
            while (!ans.empty() && nums[i] > ans.back() 
                   && (ans.size()-1) + (nums.size() - i) >= k) ans.pop_back();
            if (ans.size() < k) ans.push_back(nums[i]);
        }
        return ans;
    }
    bool compare(vector<int> &nums1, int i, vector<int> &nums2, int j) {
        while (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]) {
            ++i;++j;
        }
        if (j == nums2.size()) return true;
        if (i < nums1.size() && nums1[i] > nums2[j]) return true;
        return false;
    }
    vector<int> merge(vector<int> &nums1, vector<int> &nums2, int k) {
        vector<int> res(k, 0);
        for (int i = 0, j = 0, r = 0; r < k; ++r) {
            res[r] = compare(nums1, i, nums2, j) ? nums1[i++] : nums2[j++];
        }
        return res;
    }
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int>ans(k,0);
        int n = nums1.size();
        int m = nums2.size();
        for(int i=0;i<=min(k,n);i++){
            if(k-i>m)continue;
            vector<int>x=maxNumber(nums1,i);
            vector<int>y=maxNumber(nums2,k-i);
            vector<int>z = merge(x,y,k);
            if(compare(z,0,ans,0))ans=z;
        }
        return ans;
    }
