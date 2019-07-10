    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int>bin(nums1.begin(),nums1.end());
        int n = nums2.size();
        vector<int>ans;
        for(int i=0; i<n; i++){
            if(bin.find(nums2[i])!=bin.end()){
                bin.erase(nums2[i]);
                ans.push_back(nums2[i]);
            }
        }
        return ans;
    }
